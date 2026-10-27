---
title: "练习 1 - 自定义指令（云智能体）"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 上一课：先决条件][previous-lesson] · [下一课：GitHub Copilot 云智能体 →][next-lesson]

使用生成式 AI 时，上下文至关重要。如果任务必须按特定方式完成，或 Copilot 需要了解一些背景信息，就应确保它能访问这些内容。[指令文件][instruction-files]可以提供这些指导，让 Copilot 不仅了解要做什么，也了解应当如何完成。

本练习将介绍如何：

- 通过存储库自定义指令和按路径应用的指令文件，了解如何向 Copilot 提供项目上下文、编码指南和文档标准。
- 在 `.github/copilot-instructions.md` 中添加一条新的存储库级标准。

> [!NOTE]
> 与 VS Code 和 CLI 系列课程不同，这里不会运行“前后对比”提示词。GitHub Copilot 云智能体会异步处理 GitHub 议题，因此难以实时并排展示指令的影响。稍后审查云智能体创建的拉取请求时，你会看到指令文件的作用。

## 指令文件

### 场景

Tailspin Toys 作为一家规范的开发公司，制定了一系列开发实践指南和要求，包括：

- 数据层始终需要单元测试。
- UI 应采用深色模式并具有现代感。
- 应以 TSDoc 文档注释的形式在代码中添加说明。
- 每个文件开头都应添加一段注释，说明文件的用途。

通过使用指令文件，可以让 Copilot 获取正确的信息，并按照这些实践执行任务。

### 自定义指令

自定义指令可向 Copilot 提供上下文和偏好，帮助它理解你的编码风格和要求。它可以让你更好地引导 Copilot，获得更相关的建议和代码片段。你可以指定偏好的编码约定、库，甚至希望添加的注释类型。指令既可以适用于整个存储库，也可以针对特定文件类型提供任务级上下文。

指令文件有两种类型：

- `.github/copilot-instructions.md`：每次针对该存储库向 Copilot 提交请求时，都会发送此单一指令文件。它应包含与大多数 Copilot Chat 或 CLI 请求相关的项目级信息，例如所用技术栈、项目概述、最佳实践和全局指导。
- `.github/instructions/*.instructions.md`：可针对具体任务或文件类型创建此类文件。例如，为 TypeScript 或 Astro 提供指南，或说明如何创建 UI 组件或一组单元测试。

> [!NOTE]
> 在 IDE 中工作时，指令文件仅用于 Copilot Chat 生成代码，不适用于代码补全或下一个编辑建议。
>
> Copilot Chat、Copilot CLI 和 Copilot 云智能体在生成代码时，都会使用存储库级指令文件和带有 `applyTo` frontmatter 的 `*.instructions.md` 文件。
>
> 此外，Copilot [还支持其他标准的指令文件][custom-instructions-support]，包括 AGENTS.md 和 CLAUDE.md 文件。

### 管理指令文件的最佳实践

关于如何创建指令文件的完整介绍超出了本工作坊的范围。不过，示例项目展示了一种有代表性的方法。总体而言：

- 让 `copilot-instructions.md` 专注于项目级指导，例如项目内容、项目结构和全局编码标准。
- 使用 `*.instructions.md` 文件针对特定文件类型（如单元测试、Astro 组件或数据层）或特定任务提供指导。
- 使用自然语言，确保指导清晰，并提供代码示例说明正确和错误的写法。

创建指令文件并没有唯一的方法，使用 AI 也是如此。通过实践，你会找到适合自己项目的方法。

> [!TIP]
> 每个使用 GitHub Copilot 的项目都应有一套完善的指令文件。查看本项目的文件时，你可能会注意到其中包含多种任务的指引，例如 [UI 更新][ui-instructions]和 [Astro][astro-instructions]。
>
> Copilot 也可以帮你生成指令文件。不同产品界面的操作方式各不相同，例如 VS Code 中的 **Configure Chat → Generate Agent Instructions**，或 Copilot CLI 中的 `/init`。对应产品的课程会在相关处说明。
>
> 需要模板或起点？可以查看 [awesome-copilot][awesome-copilot]，其中收录了指令文件、自定义智能体和其他资源。

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## 浏览本项目的自定义指令文件

花些时间阅读此存储库自带的指令文件：一个核心文件 `copilot-instructions.md`，以及一组适用于不同任务的 `*.instructions.md` 文件。可以在编辑器或 GitHub 网页界面中打开这些文件。

1. 打开 `.github/copilot-instructions.md`。
2. 浏览文件，注意其中对项目的简要说明，以及 **Agent notes**、**Code standards**、**Scripts** 和 **Repository Structure** 等章节。包括嵌套的 **GitHub Actions Workflows** 指引在内，这些内容适用于你与 Copilot 的任何交互。
3. 打开 `.github/instructions` 文件夹并浏览其中的内容。你会看到 Astro 文件、Drizzle 数据层、测试等方面的指令。
4. 打开 `.github/instructions/unit-tests.instructions.md`。注意文件顶部的 `applyTo` 字段；它设置了一个相对于存储库根目录的 glob，用于决定指令适用的文件。这里，任何 TypeScript 测试文件（例如匹配 `**/*.test.ts` 的文件）都符合条件。
5. 查看此项目中创建单元测试的专用指令。
6. 最后，打开 `.github/instructions/drizzle.instructions.md` 并滚动到底部。注意其中指向其他指令文件（如 `unit-tests.instructions.md`）和项目现有文件的链接。这样可以将较大的指令集拆分成更小、可复用的文件，并为 Copilot 提供代码示例参考。这些路径相对于指令文件所在位置，而不是存储库根目录。

> [!NOTE]
> `copilot-instructions.md` 中的 **Code formatting requirements** 章节记录了项目编码标准，但尚未要求在代码中添加文档注释。接下来，你将为 TSDoc 文档注释和文件注释头添加要求。

## 添加新的存储库标准

这是本练习中唯一需要编辑的内容：添加一条项目级规则，要求以 TSDoc 文档注释和文件级注释头的形式在代码中添加说明。云智能体稍后处理你分配的议题时会采用这条规则。

编辑前，先创建一个分支（云智能体会读取议题目标分支中的指令，但仍建议将更改整洁地提交）：

1. 在 Codespace 终端中创建并切换到新分支：

   ```bash
   git checkout -b custom-instructions-cloud
   ```

如前所述，`.github/copilot-instructions.md` 用于向 Copilot 提供项目级信息。接下来添加存储库编码标准，以改进代码建议。

1. 重新打开 `.github/copilot-instructions.md`。
2. 找到 **Code formatting requirements** 章节，通常位于第 27 行附近。注意该章节记录了项目编码标准，但尚未规定代码内文档的要求，因此生成的辅助函数没有文档注释。
3. 在现有标准下方添加以下 Markdown 内容，要求 Copilot 添加文件注释头和 TSDoc 文档注释：

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. 保存 `copilot-instructions.md`。

> [!TIP]
> 如上一课所示，可以在存储库级别（`.github/copilot-instructions.md`）创建指令文件来提供全局指导，也可以为特定语言、文件类型或任务创建 `*.instructions.md` 文件。项目级标准（如刚添加的文档注释规则）适合放在存储库级文件中。

## 提交、推送并合并指令更新

云智能体会读取议题目标分支中的指令。在下一练习中将议题分配给 Copilot 时，它会从 `main` 创建分支，因此必须先将指令更改合并到 `main`，云智能体才能使用。

1. 暂存并提交更改：

   ```bash
   git add .github/copilot-instructions.md
   git commit -m "Add doc comment and file-header standards to copilot instructions"
   ```

2. 推送分支：

   ```bash
   git push -u origin custom-instructions-cloud
   ```

3. 在 github.com 上创建从 `custom-instructions-cloud` 到 `main` 的拉取请求并将其合并。这样，云智能体处理下一练习中分配的议题时便会读取这些指令。

> [!TIP]
> 如果希望在本工作坊中直接使用 `main` 分支，可以跳过创建分支的步骤，并直接提交到 `main`。此处采用分支，是为了模拟真实项目中的工作方式。

## 总结与后续步骤

你已了解 Copilot 如何从项目指令文件中获取上下文，并在 `.github/copilot-instructions.md` 中添加了一条新的存储库级标准。接下来的课程中，你会看到云智能体创建的拉取请求如何遵循这条标准。

接下来，将[第一个议题分配给 Copilot 云智能体][next-lesson]。

## 资源

- [GitHub Copilot 自定义指令文件][instruction-files]
- [创建自定义指令的最佳实践][instructions-best-practices]
- [编写更好的 Copilot 自定义指令的 5 个技巧][copilot-instructions-five-tips]
- [Awesome Copilot：指令文件及其他资源合集][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-cloud-agent/
[instruction-files]: https://docs.github.com/copilot/customizing-copilot/about-customizing-github-copilot-chat-responses
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
