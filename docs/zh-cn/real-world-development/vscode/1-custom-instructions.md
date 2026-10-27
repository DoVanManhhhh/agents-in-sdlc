---
title: "练习 1 - 自定义指令 (VS Code)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 上一课：准备工作][previous-lesson] · [下一课：智能体模式 →][next-lesson]

使用生成式 AI 时，上下文至关重要。如果某项任务需要以特定方式完成，或 Copilot 需要了解一些背景信息，就要确保它能获取这些上下文。你可以通过多种方式向 Copilot 提供特定上下文，其中一种重要方式是使用[指令文件][instruction-files]，为代码生成提供指导。

在本练习中，你将：

- 了解如何通过存储库自定义指令和按路径限定范围的指令文件，向 Copilot 提供项目上下文、编码指南和文档标准。
- 在现有指令生效的情况下，为筛选功能生成第一个数据切片（出版商辅助函数）。
- 在 `.github/copilot-instructions.md` 中添加新的存储库级标准。
- 再次发送相同提示词，观察生成的代码如何采用新标准。
- 将指令更新和筛选功能切片提交到 `main`，以便 Copilot 在下一课中使用更新后的指导。

> [!CAUTION]
> 生成的代码可能与部分标准不一致。Copilot 的输出具有非确定性。本练习的重点是观察更新指令后行为变化的**趋势**，而不是让输出与示例逐字相同。

## 指令文件

### 场景

Tailspin Toys 和任何优秀的软件开发团队一样，制定了一系列开发实践指南和要求，包括：

- 数据层始终需要单元测试。
- UI 应采用深色模式并具有现代感。
- 应以 TSDoc 文档注释的形式为代码添加文档。
- 每个文件开头都应添加一段注释，说明文件的用途。

借助指令文件，你可以确保 Copilot 获取正确的信息，并按照上述实践完成任务。

### 自定义指令

自定义指令可以向 Copilot 提供上下文和偏好，帮助它更好地理解你的编码风格和要求。这是一项强大的功能，可以引导 Copilot 提供更相关的建议和代码片段。你可以指定偏好的编码约定、库，甚至希望在代码中使用的注释类型。你可以为整个存储库创建指令，也可以为特定类型的文件创建指令，以提供任务级上下文。

指令文件有两种：

- `.github/copilot-instructions.md` 是一个指令文件，会随存储库中的**每个**请求一起发送给 Copilot。此文件应包含项目级信息，也就是与 Copilot 收到的大多数聊天或 CLI 请求都相关的上下文，例如技术栈、项目概述、最佳实践和全局指导。
- `.github/instructions/*.instructions.md` 文件可针对特定任务或文件类型创建。例如，可以为 TypeScript 或 Astro 等语言，或创建 UI 组件、编写单元测试等任务提供指导。

> [!NOTE]
> 在 IDE 中工作时，指令文件仅用于 Copilot Chat 代码生成，不适用于代码补全或下一步编辑建议。
>
> Copilot Chat、Copilot CLI 和 Copilot 云智能体在生成代码时，都会使用存储库级指令文件和带有 `applyTo` frontmatter 的 `*.instructions.md` 文件。
>
> 此外，Copilot [还支持其他标准的指令文件][custom-instructions-support]，包括 AGENTS.md 和 CLAUDE.md 文件。

### 管理指令文件的最佳实践

完整讨论如何创建指令文件超出了本工作坊的范围。不过，示例项目展示了一种有代表性的方法。总体而言：

- 将 `copilot-instructions.md` 的内容限定为项目级指导，例如项目说明、项目结构和全局编码标准。
- 使用 `*.instructions.md` 文件为特定文件类型（单元测试、Astro 组件、数据层）或特定任务提供指导。
- 使用自然语言，确保指导清晰，并提供代码示例说明推荐或不推荐的写法。

创建指令文件没有唯一的方法，使用 AI 也是如此。通过试验，你会逐渐找到适合自己项目的方法。

> [!TIP]
> 每个使用 GitHub Copilot 的项目都应该有一套完善的指令文件。在查看本项目中的指令文件时，你可能会注意到，其中包含适用于多种任务的文件，例如 [UI 更新][ui-instructions]和 [Astro][astro-instructions]。
>
> Copilot 也可以帮助你生成指令文件。不同产品界面的操作方式有所不同（例如 VS Code 中的 **Configure Chat → Generate Agent Instructions**，或 Copilot CLI 中的 `/init`）；相应课程会在适用时介绍具体操作。
>
> 需要模板或起点？可以查看 [awesome-copilot][awesome-copilot]，其中包含大量指令文件、自定义智能体和其他资源。

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## 查看本项目中的自定义指令文件

花点时间阅读此存储库提供的指令文件，其中包含一个核心 `copilot-instructions.md` 文件，以及一组适用于不同任务的 `*.instructions.md` 文件。你可以在编辑器或 GitHub 网页界面中打开这些文件。

1. 打开 `.github/copilot-instructions.md`。
2. 浏览文件，留意项目简介以及 **Agent notes**、**Code standards**、**Scripts** 和 **Repository Structure** 等章节。在 **Code standards** 下，留意其中的 **GitHub Actions Workflows** 子章节。这些内容适用于你与 Copilot 的所有交互。
3. 打开 `.github/instructions` 文件夹并查看其中内容。你会看到适用于 Astro 文件、Drizzle 数据层、测试等内容的指令。
4. 打开 `.github/instructions/unit-tests.instructions.md`。留意顶部的 `applyTo` 字段，它设置了一个相对于存储库根目录的 glob，用于确定指令适用的文件。这里，任何匹配 `**/*.test.ts` 的 TypeScript 测试文件都会应用这些指令。
5. 留意此项目中有关创建单元测试的具体指令。
6. 最后，打开 `.github/instructions/drizzle.instructions.md` 并滚动到文件底部。留意其中指向其他指令文件（例如 `unit-tests.instructions.md`）和项目现有文件的链接。这样，你可以把较大的指令集拆分成较小且可复用的文件，并为 Copilot 提供可遵循的示例。这里的路径相对于指令文件本身，而不是存储库根目录。

> [!NOTE]
> `copilot-instructions.md` 中的 **Code formatting requirements** 部分介绍了项目的编码标准，但尚未要求为代码添加文档。接下来的步骤会添加 TSDoc 文档注释和文件注释标题的规则。

## 为更改创建分支

接下来按照最佳实践，为更改创建一个分支。

1. 返回上一练习中使用的 Codespace。
2. 按 <kbd>Control</kbd>+<kbd>\`</kbd>（Mac）或 <kbd>Ctrl</kbd>+<kbd>\`</kbd>（Windows/Linux）打开新终端。
3. 创建并切换到新分支：

   ```bash
   git checkout -b custom-instructions
   ```

## 更新指令前先使用 Copilot Chat

> [!TIP]
> **打开 Copilot Chat**
>
> 开始以下练习前，返回 Codespace，打开 Copilot Chat 面板，然后选择 **New Chat** 开始干净的对话。不同练习所用的模式和模型可能不同；相关步骤会注明需要选择的选项。

要查看自定义指令的影响，先在当前指令文件生效的情况下发送提示词。稍后，你将更新指令文件并再次发送相同提示词，查看结果有何变化。

1. 关闭之前练习中打开的编辑器选项卡，确保 Copilot 只获取你想要的上下文。
2. 打开 `src/lib/publishers.ts`，让 Copilot 知道辅助函数应该放在哪里。
3. 在 Chat 视图的智能体下拉列表中选择 **Agent**，让 Copilot 应用文件更改。

   ![Chat 视图中的智能体选择器截图](../../../_images/shared-chat-mode-selector.png)

4. 发送以下提示词：

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

5. Copilot 会探索项目并应用代码更新，通常会同时修改辅助函数文件和测试。
6. 注意，建议的辅助函数是一个有类型的函数，它将 `db` 客户端作为第一个参数，并返回有类型的出版商数组。这来自 `.github/instructions/drizzle.instructions.md` 中的数据层约定（该文件适用于 `src/lib/*.ts`）。
7. 注意，建议的代码**缺少** TSDoc 文档注释和文件级注释标题。

> [!CAUTION]
> 由于 Copilot 的输出具有概率性，即使没有明确要求，也可能添加文档注释。即便如此也没关系，本练习的重点是观察更新指令后行为是否更加**一致**。

## 添加新的存储库标准

如前所述，`.github/copilot-instructions.md` 用于向 Copilot 提供项目级信息。我们来补充存储库编码标准，以改进代码建议。

1. 重新打开 `.github/copilot-instructions.md`。
2. 找到 **Code formatting requirements** 部分，通常在第 27 行附近。注意该部分说明了项目编码标准，但尚未规定代码文档要求，因此生成的辅助函数没有文档注释。
3. 在现有标准下方添加以下 Markdown 内容，要求 Copilot 添加文件注释标题和 TSDoc 文档注释：

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. 保存 `copilot-instructions.md`。

> [!TIP]
> 如上一课所示，指令文件既可以放在存储库级别（`.github/copilot-instructions.md`），为整个项目提供指导；也可以使用 `*.instructions.md` 文件为特定语言、文件类型或任务提供指导。刚刚添加的文档注释规则属于项目级标准，因此存储库级文件是合适的位置。

## 再次发送提示词并观察变化

1. 返回 Copilot Chat 并选择 **New Chat**，清空对话内容。
2. 再次选择 `src/lib/publishers.ts`，让 Copilot 聚焦于正确的文件。
3. 发送与之前相同的提示词：

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

4. 注意，现在建议的文件开头有类似以下内容的注释块：

   ```typescript
   /**
    * Publisher data-access helpers for the Tailspin Toys Crowd Funding platform.
    * Provides functions to retrieve publisher information from the database.
    */
   ```

5. 注意，现在建议的函数还包含类似以下内容的 TSDoc 注释：

   ```typescript
   /**
    * Returns a list of all publishers with their id and name.
    *
    * @param db - The Drizzle database client.
    * @returns A promise that resolves to an array of publisher objects.
    */
   ```

你刚刚引导 Copilot 遵循新的项目标准，并将其应用到真实代码中；下一课将基于此代码继续开发。

## 提交指令并推送分支

指令文件与其他项目资源一样，也需要使用版本控制进行管理。现在，将它们与其他文件一样提交并推送到存储库。

1. 按 <kbd>Control</kbd>+<kbd>\`</kbd>（Mac）或 <kbd>Ctrl</kbd>+<kbd>\`</kbd>（Windows/Linux）打开新终端窗口。
2. 在终端中运行以下命令，确认指令更新和辅助函数更改均已存在：

   ```bash
   git status
   ```

3. 在终端中暂存并提交指令更新，以及 Copilot 为辅助函数基础所做的所有更改：

   ```bash
   git add .github/copilot-instructions.md src/lib/publishers.ts
   # If git status shows additional supporting updates (for example tests), add those files too.
   git commit -m "Add doc comment standards and publishers helper foundation"
   ```

4. 将分支推送到存储库：

   ```bash
   git push -u origin custom-instructions
   ```

## 创建并合并拉取请求

分支推送完成后，接下来创建拉取请求，并将它关联到待办列表中的文档标准议题。你可以手动操作，不过现有 GitHub 工具已经连接到项目，可以让 Copilot 代劳。向 Copilot 提示，让它查找议题、创建关联该议题的 PR，然后合并 PR。

> [!NOTE]
> 这是第一次让 Copilot 代表你在 GitHub 上执行操作。项目模板已经将 GitHub 工具连接到工作区，因此无需额外设置。Copilot 首次使用其中一个工具时，VS Code 可能会提示你登录 GitHub。按照提示完成登录即可。稍后的练习中，我们会介绍这种连接所用的模型上下文协议 (Model Context Protocol)。

1. 在 Codespace 中打开 Copilot Chat。
2. 按 <kbd>Control</kbd>+<kbd>Command</kbd>+<kbd>I</kbd>（Mac）或 <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>I</kbd>（Windows/Linux）打开 Copilot Chat 视图，并确保在智能体选择器中选中 **Agent**。
3. 让 Copilot 查找与更新指令文件相关的议题，并从当前分支创建 PR，同时说明指令更新和新的出版商辅助函数基础：

   ```
   Find the issue related to updating the instructions file. Create a new PR from the current branch, highlight that the PR closes that issue, and include that we also added the publishers helper foundation for the upcoming filtering work.
   ```

4. Copilot 会开始查找议题并创建 PR。
5. Copilot 提示你允许它代表你执行 GitHub 操作时，请查看命令，并酌情选择 **Allow**。
6. 创建 PR 后，让 Copilot 合并 PR，并将本地分支切回 main，提示词如下：

   ```
   Merge the PR into main. Then return to main locally, and pull the latest code so we are up to date.
   ```

7. Copilot 提示你允许它代表你执行 GitHub 操作和运行 shell 命令时，请查看命令，并酌情选择 **Allow**。

你已借助 GitHub Copilot 创建并合并了拉取请求！

## 总结与后续步骤

你了解了 Copilot 如何从本项目的指令文件中获取上下文，并在 VS Code 中使用 Copilot Chat 来：

- 发送代码生成提示词，观察 Copilot 在**现有**指令下生成的内容。
- 在 `.github/copilot-instructions.md` 中添加新的存储库级标准。
- 再次发送相同提示词，观察建议的代码如何采用新标准。
- 将指令更新和辅助函数基础提交到 `main`，以便下一课继续开发。

接下来，你将在[智能体模式][next-lesson]中运用这些指令，让 Copilot 跨代码库添加新功能。

## 资源

- [用于自定义 GitHub Copilot 的指令文件][instruction-files]
- [创建自定义指令的最佳实践][instructions-best-practices]
- [编写更好的 Copilot 自定义指令的 5 个技巧][copilot-instructions-five-tips]
- [GitHub Copilot 个人自定义指令][personal-instructions]
- [Awesome Copilot — 指令文件和其他资源合集][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-agent-mode/
[instruction-files]: https://code.visualstudio.com/docs/copilot/copilot-customization
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[personal-instructions]: https://docs.github.com/copilot/customizing-copilot/adding-personal-custom-instructions-for-github-copilot
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
