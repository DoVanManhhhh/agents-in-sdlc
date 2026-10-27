---
title: "练习 2 - GitHub Copilot 云智能体"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← 上一课：自定义指令][previous-lesson] |
|:--|

几乎所有组织都会面临技术债务，例如尚未解决的安全问题、需要更新的旧代码，或因缺少时间而长期搁置在待办列表中的功能请求。GitHub Copilot 云智能体能够自主执行更新代码、添加功能等任务。智能体完成工作后，会生成一个草稿 PR，供开发人员审查。这样可以把繁琐的任务交给智能体，加快开发流程，让开发人员专注于更重要的工作。

你将在本课中探索如何使用 Copilot 云智能体：

- 自定义代码生成环境。
- 确保操作安全。
- 了解明确界定任务范围的重要性。
- 将议题分配给 Copilot。

## 场景

Tailspin Toys 有一些希望解决的技术债务。最初受聘开发网站的承包商没有妥善编写文档——事实上，你会发现项目完全缺少文档。首先，他们希望为应用程序中所有导出的函数添加 TSDoc 文档注释。

此外，设计团队准备改进游戏发现体验。他们希望每款游戏的详情页面都显示相关游戏，也就是同一类别中的其他游戏。暂时不需要完善的实现，只需要一个可用于验收测试用户体验的版本。目前这项工作受到了阻碍，不过还有其他优先级更高的议题。

这两项任务都可能很快被降级为低优先级，因此很适合分配给 Copilot 云智能体。Copilot 云智能体可以异步处理这些任务，让开发人员先处理其他工作，之后再回来审查 Copilot 的成果并确认一切符合预期。

## 了解 GitHub Copilot 云智能体

[GitHub Copilot 云智能体](https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent#overview-of-copilot-cloud-agent-formerly-copilot-coding-agent)可以在后台执行任务，方式与人工开发人员大致相同。就像与人工开发人员协作一样，你可以通过多种方式启动任务，包括[将 GitHub 议题分配给 Copilot](https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions)。分配任务后，Copilot 会创建一个草稿拉取请求来跟踪进度、设置环境，然后开始处理任务。你可以在 Copilot 会话进行期间或完成后查看会话。建议方案准备好供你审查时，Copilot 会在拉取请求中提及你。

## 明确界定指令范围的重要性

GitHub Copilot 并非魔法——它不会替你省去思考。看似简单的操作，深入分析后也会变得复杂，因此[为 Copilot 云智能体明确界定任务范围][cloud-agent-best-practices]非常重要。请把它当作 AI 结对程序员：分阶段开展工作，在过程中学习、试验并调整。加入生成式 AI 并不会改变软件开发的基本原则。

## 此存储库中的自定义指令

前面的练习介绍了自定义指令及其如何引导 Copilot。如果你已经完成自定义指令的练习，就会看到 `.github/copilot-instructions.md` 的实际效果；如果还没有，现在正好可以快速查看。将工作分配给 Copilot 云智能体之前，先以只读方式查看存储库中已有的指令文件，稍后就能观察它们带来的影响。

请在存储库的 GitHub 网页界面中打开以下文件；如果已启动 Codespace，也可以在那里打开：

- `.github/copilot-instructions.md` - 查看 **Code standards** 部分，尤其要留意 TypeScript 约定和 TSDoc 文档注释相关要求。
- `.github/instructions/unit-tests.instructions.md` - 注意 `applyTo` frontmatter，它会将这些指令限定应用于 `**/*.test.ts` 文件。

在下一节中将 `Code lacks documentation` 议题分配给云智能体时，留意生成的拉取请求是否包含 TSDoc 文档注释、TypeScript 约定和注释标题——这些要求来自上述指令文件。后续练习中审查 PR 时，我们还会再次提到这一点。

## 为 Copilot 云智能体设置开发环境

无论由谁编写代码，通常都需要特定环境并运行一些设置脚本，以确保一切就绪。将任务分配给 Copilot 时也是如此，因为它会像软件工程师一样执行任务。

云智能体使用 [GitHub Actions][github-actions]环境来完成工作。你可以通过创建一个[专用设置工作流][setup-workflow]来自定义环境，并将其配置在 `.github/workflows/copilot-setup-steps.yml` 文件中，使其在 Copilot 开始工作前运行。这样，云智能体就能使用所需的开发工具和依赖项。为了让练习流程顺利进行并提供学习机会，我们已预先配置此工作流，确保 Copilot 可以使用 Node.js、项目依赖项、端到端测试所需的浏览器二进制文件，以及已迁移并填充数据的单 Astro 应用 SQLite 数据库：

```yaml
name: "Copilot Setup Steps"

# Allows you to test the setup steps from your repository's "Actions" tab
on: workflow_dispatch

env:
  ASTRO_TELEMETRY_DISABLED: "1"

jobs:
  copilot-setup-steps:
    runs-on: ubuntu-latest
    # Set the permissions to the lowest permissions possible needed for *your steps*. Copilot will be given its own token for its operations.
    permissions:
      # If you want to clone the repository as part of your setup steps, for example to install dependencies, you'll need the `contents: read` permission. If you don't clone the repository in your setup steps, Copilot will do this for you automatically after the steps complete.
      contents: read
    steps:
      - name: Checkout code
        uses: actions/checkout@v5

      # Frontend / app setup - Node.js (the whole app is now Astro + Drizzle/libSQL)
      - name: Set up Node.js
        uses: actions/setup-node@v6
        with:
          node-version: "lts/*"
          cache: "npm"
          cache-dependency-path: "./package-lock.json"

      - name: Install JavaScript dependencies
        run: npm ci

      - name: Install Playwright browsers
        run: npx playwright install --with-deps chromium

      # Migrate + seed the local SQLite database so builds and tests have data.
      - name: Set up the database
        run: npm run db:setup
```

这看起来与其他 GitHub 工作流文件相同，但有几个关键点：

- 文件中只有一个名为 `copilot-setup-steps` 的作业。Copilot 开始处理拉取请求之前，GitHub Actions 会先运行此作业。
- 注意 `workflow_dispatch` 触发器。它允许你从存储库的 **Actions** 选项卡手动运行工作流。这有助于测试工作流是否成功运行，不必等待 Copilot 启动它。

## 添加文档

每个人都知道文档的重要性，但大多数项目的信息要么已经过时，要么完全缺失。这类技术债务往往得不到处理，降低了工作效率，也让维护代码库或引入新开发人员变得更加困难。幸运的是，Copilot 擅长编写文档，因此非常适合将这项工作分配给 Copilot 云智能体。它会在后台生成所需文档。后续练习中，你会回来审查它的成果。

1. 在新的浏览器选项卡中打开 github.com 上的存储库。
2. 选择 **Issues** 选项卡。
3. 选择 **New issue**，打开新建议题对话框。
4. 选择 **Blank issue**，创建空白议题。
5. 将 **Title** 设置为 `Code lacks documentation`。
6. 将 **Description** 设置为：

    ```plaintext
    Our organization has a requirement that functions and methods include TSDoc doc comments where helpful. Unfortunately, recent updates haven't followed this standard. We need to update the existing code to ensure doc comments are included where they clarify behavior.
    ```

7. 选择 **Create** 创建议题。
8. 在右侧选择 **Assign to Copilot**，打开分配对话框。

  ![将议题分配给 Copilot](../../../_images/shared-assign-copilot.png)

9. 选择 **Assign**。

  ![Copilot 议题分配详情](../../../_images/ex4-assign-copilot-details.png)

10. 选择 **Pull Requests** 选项卡。
11. 打开新生成的拉取请求 (PR)，其标题类似于 `[WIP]: Code lacks documentation`。如果列表中没有出现新 PR，请稍等片刻，然后刷新浏览器窗口。
12. 几分钟后，你应该会看到 Copilot 创建了一个待办事项列表。

> [!NOTE]
> Copilot 的待办事项列表可能需要几分钟才会显示在 PR 中。Copilot 正在创建环境（运行前面介绍的工作流）、分析项目并确定解决问题的最佳方法。

13. 查看列表及 Copilot 将要完成的任务。
14. 向下滚动拉取请求时间线，你应该会看到 Copilot 已开始处理此议题。
15. 选择 **View session** 按钮。

  ![Copilot 会话视图](../../../_images/ex4-view-session.png)

> [!CAUTION]
> 你可能需要刷新窗口才能看到更新后的状态指示器。

16. 注意，你可以滚动查看实时会话，了解 Copilot 如何解决问题，包括探索代码并了解当前状态、暂停思考并决定合适的计划，以及编写代码。

这可能需要几分钟。Copilot 云智能体的主要目标之一是异步执行任务，让我们可以专注于其他工作。接下来，我们将利用这一功能：先把另一项任务分配给 Copilot 云智能体，再转而编写代码，为应用添加功能。

## 为游戏详情页面添加相关游戏部分

如前所述，GitHub Copilot 云智能体的一大优势是可以拆分工作：你专注于一组任务，智能体同时处理另一组。为设计团队添加相关游戏部分可能不需要很长时间，但这段时间仍可用于处理其他任务。我们来把它分配给 Copilot 云智能体吧！

1. 返回 github.com 上的存储库。
2. 选择 **Issues** 选项卡。
3. 选择 **New issue**，打开新建议题对话框。
4. 选择 **Blank issue**，使用空白模板。
5. 将 **Title** 设置为 `Show related games on the game details page`。
6. 将 **Description** 设置为：

    ```markdown
    We want to help people discover more games by showing related games on each game's details page. The design team wants to explore the UX and do some acceptance testing. Our requirements are:

   - Add a data-access helper in `src/lib/` that returns other games in the same category as a given game, excluding that game
   - Show a "Related games" section on the game details page that uses the helper
   - Handle the case where a game has no related games
   - There should be unit tests created for the new helper
   - Before creating the PR, ensure all tests pass
    ```

7. 选择 **Create** 创建议题。
8. 在右侧选择 **Assign to Copilot**，打开分配对话框。

  ![将议题分配给 Copilot](../../../_images/shared-assign-copilot.png)

9. 选择 **Assign**。

不久后，你应该会在议题的第一条评论中看到一组 👀，表示 Copilot 已开始处理！

![Copilot 使用眼睛表情符号表示正在处理议题](../../../_images/ex4-issue-eyes-emoji.png)

Copilot 正在认真处理你的第二项请求！Copilot 云智能体的工作方式类似软件工程师，因此你不必主动监控，而是可以等任务完成后再审查结果。现在，我们把注意力转向创建和使用自定义智能体。

## 总结与后续步骤

本课介绍了 [GitHub Copilot 云智能体][copilot-agents]。使用云智能体，可以将议题分配给 Copilot 并让它异步处理。你可以用 Copilot 解决技术债务、创建新功能，或协助将代码从一个框架迁移到另一个框架。

你探索了以下概念：

- 自定义代码生成环境。
- 确保操作安全。
- 了解明确界定任务范围的重要性。
- 将议题分配给 Copilot。

云智能体正在后台处理任务。现在我们可以转而创建和使用自定义智能体。[Copilot 云智能体也可以使用 MCP 服务器][cloud-agent-mcp]，并且能够使用自定义指令；我们已在前面的模块中介绍过这些内容。

## 资源

- [关于 Copilot 云智能体][copilot-agents]
- [将 GitHub 议题分配给 Copilot][assign-issue]
- [Copilot 云智能体设置工作流最佳实践][cloud-agent-best-practices]

| [下一课：自定义智能体 →][next-lesson] |
|--:|

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-custom-agents/
[cloud-agent-mcp]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/extend-cloud-agent-with-mcp
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[github-actions]: https://docs.github.com/actions
