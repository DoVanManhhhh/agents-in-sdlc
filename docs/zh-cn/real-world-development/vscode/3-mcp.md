---
title: "练习 3 - 使用 Playwright MCP 服务器测试功能"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 上一课：智能体模式][previous-lesson] · [下一课：自定义智能体 →][next-lesson]

你刚刚使用智能体模式构建了筛选功能。创建拉取请求之前，应该确认它在浏览器中能够正常运行。你不必自己逐项点击应用，可以连接 **Playwright MCP 服务器**，让 Copilot 控制真实浏览器为你测试功能，然后发布分支并创建 PR。

在本练习中，你将：

- 了解什么是模型上下文协议 (MCP)，以及 MCP 服务器如何通过新工具扩展 Copilot 的能力。
- 将 Playwright MCP 服务器添加到工作区。
- 让 Copilot 使用该服务器在浏览器中手动测试筛选功能。
- 发布分支，并为筛选功能创建拉取请求。

## 什么是模型上下文协议 (MCP)？

智能体模式可以连接 IDE 之外的服务，功能会更加强大。Copilot 使用模型上下文协议 (MCP) 来实现这一点：这是智能体与外部工具和服务通信的标准方式。

![智能体模式的内部工作原理图，展示其与上下文、LLM 和工具的交互，包括由 MCP 服务器和 VS Code 扩展提供的工具](../../../_images/ex1-mcp-diagram.png)

[模型上下文协议 (MCP)](https://github.blog/ai-and-ml/llms/what-the-heck-is-mcp-and-why-is-everyone-talking-about-it/) 为 AI 智能体提供了与外部工具和服务通信的方式。借助 MCP，AI 智能体可以实时访问外部工具和服务。它们可以通过资源获取最新信息，也可以通过工具代表你执行操作。

这些工具和资源通过 MCP 服务器访问。MCP 服务器充当 AI 智能体与外部工具和服务之间的桥梁，负责管理智能体与外部工具（例如现有 API 或 npm 包等本地工具）之间的通信。每个 MCP 服务器都代表 AI 智能体可以访问的一组不同工具和资源。

以下是几个常见的 MCP 服务器：

- **[GitHub MCP 服务器](https://github.com/github/github-mcp-server)**：提供一组用于管理 GitHub 存储库的 API。AI 智能体可以使用它执行创建新存储库、更新现有存储库以及管理议题和拉取请求等操作。
- **[Playwright MCP 服务器](https://github.com/microsoft/playwright-mcp)**：使用 Playwright 提供浏览器自动化能力。AI 智能体可以使用它执行打开网页、填写表单和选择按钮等操作。

还有许多其他 MCP 服务器，可用于访问不同的工具和资源。GitHub 提供了一个 [MCP 注册表](https://github.com/mcp)，帮助大家发现 MCP 服务器并为其生态系统做贡献。

> [!CAUTION]
> 在安全方面，应像对待项目的其他依赖项一样对待 MCP 服务器。使用 MCP 服务器前，请仔细审查其源代码、验证发布者，并考虑安全影响。只使用你信任的 MCP 服务器，并谨慎授予其访问敏感资源或执行敏感操作的权限。

## 查看 MCP 配置

`.vscode/mcp.json` 文件用于配置此 VS Code 工作区中可用的 MCP 服务器。

1. 在 Codespace 中打开 `.vscode/mcp.json`。
2. 你应该会看到已经为你配置的 `github` 服务器：

    ```json
    {
      "servers": {
        "github": {
          "type": "http",
          "url": "https://api.githubcopilot.com/mcp/"
        }
      }
    }
    ```

此项目模板中预先配置了 `github` 条目，因此 Copilot 能在上一课中读取你的待办议题。它使用[远程 GitHub MCP 服务器][remote-github-mcp-server]，无需在本地安装任何内容。VS Code 会通过 HTTP 连接到服务器，而你只需在 Copilot 首次使用其中某个工具时登录 GitHub。

## 添加 Playwright MCP 服务器

接下来要添加第二个服务器。[Playwright MCP 服务器][playwright-mcp-server]可以让 Copilot 控制浏览器，正好适合用来测试功能。

1. 在 `.vscode/mcp.json` 中，在 `github` 旁边添加 `playwright` 条目，使文件内容如下：

    ```json
    {
      "servers": {
        "github": {
          "type": "http",
          "url": "https://api.githubcopilot.com/mcp/"
        },
        "playwright": {
          "command": "npx",
          "args": ["@playwright/mcp@latest", "--headless"]
        }
      }
    }
    ```

2. 保存文件。

与远程 `github` 服务器不同，`playwright` 是一个**本地**服务器：VS Code 会在你的计算机上运行 `npx @playwright/mcp@latest` 来启动它。`--headless` 标志会让 Playwright 在后台运行浏览器，不显示可见窗口。Codespace 中没有桌面环境来显示窗口，因此必须使用此标志。

> [!NOTE]
> Tailspin Toys 项目已在端到端测试中使用 Playwright，因此通常已经安装了 Playwright 所需的浏览器。如果 Copilot 随后报告缺少浏览器，请让它运行 `npx playwright install chromium`，然后重试。

## 启动并信任服务器

VS Code 会**按需启动** MCP 服务器：Copilot 首次需要服务器工具时，VS Code 会启动服务器，并询问你是否信任它。

1. 在 `.vscode/mcp.json` 中，`playwright` 条目上方会显示 **Start** 操作。选择它以立即启动服务器，并确认配置正确。
2. 如果 VS Code 要求确认是否信任服务器，请检查配置并选择信任，以便服务器启动。

手动启动是可选操作。如果跳过此步骤，VS Code 会在下一步中 Copilot 首次需要使用服务器工具时启动服务器，并询问你是否信任它。

## 测试筛选功能

[Playwright MCP 服务器][playwright-mcp-server]可让 Copilot 控制真实浏览器。你无需自己逐项点击应用来检查代码，智能体可以打开页面、导航、应用筛选条件、读取结果并向你总结观察到的内容。无需离开对话即可快速确认功能是否符合预期。

在底层，Playwright MCP 服务器依赖页面的[无障碍树][playwright-mcp-server]，而不是截图。这意味着智能体会像辅助技术一样，根据结构化且带标签的元素（按钮、链接、列表项）进行推理，因此快速功能检查也能兼作简单的无障碍检查。

连接服务器并启动应用后，提示 Copilot 测试刚刚构建的筛选功能：

```text
Using the Playwright MCP server, open a browser to the running app at http://localhost:4321 and verify the new game filtering feature:

1. Go to the games page and note how many games are listed.
2. Apply a category filter and confirm the list updates to only show games in that category.
3. Clear it, then apply a publisher filter and confirm the list updates to that publisher.
4. Combine a category and a publisher filter and confirm the results respect both.

Report what you observe at each step, and call out anything that does not behave as expected.
```

Copilot 会通过 Playwright MCP 服务器启动浏览器并逐步执行测试，然后向你报告结果。根据议题中的验收标准审阅摘要；如果发现问题，可以继续提问，或让 Copilot 在创建拉取请求之前修改代码。

> [!NOTE]
> 执行此测试时，应用必须运行在 `http://localhost:4321`。如果开发服务器已停止，请在发送提示词前重新启动。Copilot 首次使用 Playwright MCP 服务器时，可能需要下载浏览器。如果报告缺少浏览器，请让它运行 `npx playwright install chromium`，然后重试。

[playwright-mcp-server]: https://github.com/microsoft/playwright-mcp

## 发布分支并创建拉取请求

确认功能正常后，就可以创建拉取请求 (PR)，让团队审查。首先发布 `filtering-vscode` 分支。

1. 在 Codespace 中打开 **Source Control** 面板，查看 Copilot 所做的更改。
2. 选择 **+** 图标暂存更改。
3. 使用 **Sparkle** 按钮生成提交消息。

   ![显示 Copilot 更改的 Source Control 面板截图](../../../_images/ex3-source-control-changes.png)

4. 选择 **Publish**，将分支推送到存储库。

## 创建拉取请求

创建拉取请求有多种方式，包括使用 github.com 和 GitHub 命令行接口 (CLI)。不过，既然已经在使用 GitHub Copilot，就让它来创建 PR 吧！Copilot 可以查找相关议题并创建与其关联的 PR。

1. 打开 Copilot Chat 面板，选择 **New Chat** 开始新会话。
2. 确保在智能体下拉列表中选择 **Agent**，这样 Copilot 才能使用 GitHub 工具。
3. 提示 Copilot 创建 PR：

   ```plaintext
   Find the issue in the repo related to filtering by category and publisher. Create a new pull request for the current branch, and associate it with the correct issue.
   ```

4. 根据需要选择 **Continue**，允许 Copilot 执行收集信息和操作所需的任务。首次使用 GitHub 工具时，系统可能会提示你登录 GitHub，请按照提示操作。
5. 留意 Copilot 如何搜索议题、找到正确的议题并创建 PR。
6. 选择 Copilot 生成的链接查看拉取请求，但**暂时不要合并**。

## 总结与后续步骤

恭喜！在本练习中，你：

- 了解了模型上下文协议 (MCP)，以及 MCP 服务器如何通过新工具扩展 Copilot 的能力。
- 将 Playwright MCP 服务器添加到工作区。
- 使用该服务器在浏览器中手动测试筛选功能。
- 发布了分支，并为筛选功能创建拉取请求。

你使用 MCP 服务器测试了功能，但 MCP 只是扩展 Copilot 能力的一种方式。接下来，我们将[创建自定义智能体][next-lesson]，以简化无障碍审查等专项任务。

## 资源

- [什么是 MCP，为什么大家都在讨论它？][mcp-blog-post]
- [Microsoft Playwright MCP 服务器][playwright-mcp-server]
- [GitHub MCP 服务器][github-mcp-server]
- [GitHub MCP 注册表][mcp-registry]
- [VS Code 中的 MCP 服务器][vscode-mcp-config]

[previous-lesson]: ../2-agent-mode/
[next-lesson]: ../4-custom-agents/
[mcp-blog-post]: https://github.blog/ai-and-ml/llms/what-the-heck-is-mcp-and-why-is-everyone-talking-about-it/
[github-mcp-server]: https://github.com/github/github-mcp-server
[mcp-registry]: https://github.com/mcp
[remote-github-mcp-server]: https://github.blog/changelog/2025-06-12-remote-github-mcp-server-is-now-available-in-public-preview/
[vscode-mcp-config]: https://code.visualstudio.com/docs/agents/reference/mcp-configuration
