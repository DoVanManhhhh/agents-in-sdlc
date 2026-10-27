---
title: "练习 4 - 自定义智能体"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

## 什么是自定义智能体？

GitHub Copilot 中的[自定义智能体][custom-agents-concept]是针对开发工作流中的特定任务或领域定制的 AI 助手。你可以通过存储库 `.github/agents` 文件夹中的 Markdown 文件定义智能体，为 Copilot 提供有针对性的指令、最佳实践、编码模式和领域知识，帮助它更有效地完成特定类型的工作。团队可以将专业知识编写成可复用的智能体，例如执行 [WCAG][wcag] 合规检查的无障碍智能体、遵循安全编码实践的安全智能体，或维护一致测试模式的测试智能体。

自定义智能体通过项目 `.github/agents` 文件夹中的 Markdown 文件定义，也可以全局存放在 `~/.copilot/agents` 中。每个文件都包含 YAML frontmatter，至少需要 `name` 和 `description` 字段；随后是定义智能体行为、专业知识和指令的 Markdown 提示词。

### 自定义智能体与智能体技能的比较

自定义智能体与[智能体技能][agent-skills-concept]在逻辑上有一些重叠。两者主要通过 Markdown 文件定义，都会告诉 AI 如何执行操作。最简单的区分方式是：**自定义智能体**是执行工作的人员，**技能**则是工具。

自定义智能体拥有自己的上下文窗口，并负责协调技能（甚至其他智能体）来完成工作。在本实验中，无障碍自定义智能体会根据无障碍指南审查和更新网站；在执行过程中，它可以调用拉取请求工作流技能或运行和管理测试的技能。

> [!NOTE]
> 编写自定义智能体没有唯一的正确方式。与 AI 相关的任何工作一样，都需要通过测试和迭代，找到适合你环境和场景的方案。

[custom-agents-concept]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[agent-skills-concept]: https://docs.github.com/copilot/concepts/agents/about-agent-skills
[wcag]: https://www.w3.org/WAI/standards-guidelines/wcag/

## 场景

Tailspin Toys 致力于让所有用户都能访问其众筹平台，不受视觉能力或偏好的影响。最近收到的用户反馈指出，由于文本与背景颜色对比度不足，一些用户觉得当前深色主题难以阅读。为解决这一无障碍问题，设计团队要求实现一个可以切换的高对比度模式。

无障碍功能至关重要，因此你希望尽快实现。接下来将使用自定义智能体生成此功能。

在本练习中，你将：

- 查看现有的无障碍自定义智能体。
- 在 Copilot Chat 中使用无障碍智能体实现高对比度模式。

## 查看无障碍自定义智能体

我们已经为你创建了一个无障碍自定义智能体。先查看其内容，了解它将如何引导 Copilot。

返回 Codespace，然后打开终端，从 `main` 创建一个新的分支来单独处理无障碍功能（练习 3 中的筛选 PR 将保留在另一个分支中）：

```bash
git checkout main
git pull
git checkout -b accessibility-vscode
```

1. 打开 `.github/agents/accessibility.md`。
2. 留意包含 `name` 和 `description` 字段的 YAML frontmatter。

> [!CAUTION]
> `name` 和 `description` frontmatter 是自定义智能体的必需字段。

3. 接着浏览并查看后续章节，其中包括：
   - 为无障碍网站生成代码时的核心职责。
   - 无障碍最佳实践。
   - HTML、CSS 和 JavaScript 代码示例。
   - 常见问题和错误列表。

## 在 Copilot Chat 中使用自定义智能体

VS Code 会在 Copilot Chat 视图底部的智能体下拉列表中显示 `.github/agents` 中定义的所有自定义智能体。你可以选择自定义智能体，让聊天会话使用该智能体的指令和工具。

> [!TIP]
> **打开 Copilot Chat**
>
> 开始以下练习前，返回 Codespace，打开 Copilot Chat 面板，然后选择 **New Chat** 开始干净的对话。不同练习所用的模式和模型可能不同；相关步骤会注明需要选择的选项。

1. 如果 Chat 视图的智能体下拉列表中尚未选择 **Agent**，请选择它。

   ![Chat 视图中的智能体选择器截图](../../../_images/shared-chat-mode-selector.png)

2. 选择 Chat 视图底部的智能体下拉列表（其中显示当前智能体，默认为 **default**）。
3. 从可用智能体列表中选择 **Accessibility agent**。
4. 向无障碍智能体发送以下提示词：

    ```plaintext
    Add a high-contrast mode to the site. There should be a toggle for high contrast which the user can set, and the setting should persist across page reloads using local storage on the browser.
    ```

5. Copilot Chat 将开始工作：探索代码库、提出更改并编辑项目文件。每项编辑都会以内联方式显示在聊天中，并包含文件路径和供你审查的差异。
6. 编辑应用后，**Files changed** 指示器会更新，让你查看智能体在工作期间修改的文件集合。

> [!NOTE]
> 此过程可能需要几分钟。Copilot 会实际修改存储库中的文件，例如 Astro 组件、CSS 和相关测试。

下一课将介绍如何审查并引导这项尚在进行中的工作。

## 总结与后续步骤

本课介绍了 [GitHub Copilot 中的自定义智能体][custom-agents]，也就是针对特定任务和领域定制的 AI 助手。借助自定义智能体，你可以将团队的专业知识和标准编写成可复用智能体，帮助 Copilot 更有效地完成特定类型的工作。

你探索了以下概念：

- 自定义智能体的定义方式。
- 在 Copilot Chat 智能体模式中使用自定义智能体。

接下来，你将[监控并引导智能体的工作][next-lesson]，实时审查更改，并在同一会话中添加浅色模式切换开关。

## 资源

- [关于自定义智能体][custom-agents]
- [在 IDE 中创建自定义智能体][creating-custom-agents-ide]
- [VS Code 中的自定义智能体][custom-agents-vscode]
- [自定义智能体配置][custom-agents-config]
- [awesome-copilot 上的自定义智能体][awesome-copilot-agents]

---

| [← 上一课：使用 Playwright MCP 服务器测试功能][previous-lesson] | [下一课：监控和管理智能体 →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-mcp/
[next-lesson]: ../5-managing-agents/
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[creating-custom-agents-ide]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/create-custom-agents-in-your-ide
[custom-agents-vscode]: https://code.visualstudio.com/docs/copilot/customization/custom-agents
[custom-agents-config]: https://docs.github.com/copilot/reference/custom-agents-configuration
[awesome-copilot-agents]: https://github.com/github/awesome-copilot/tree/main/agents
