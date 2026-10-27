---
title: "练习 4 - 使用自定义指令引导 Copilot"
description: "查看存储库指令、添加文档标准，并将其应用于筛选代码。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

使用生成式 AI 时，上下文至关重要。如果任务必须按特定方式完成，就应确保 Copilot 能获取相应指导。[指令文件][instruction-files]不仅说明你想要什么代码，也说明代码应如何组织。现在筛选功能已经完成，你将探索 Copilot 使用的指令、添加文档标准，并将其应用于代码。

本课将介绍如何：

- 了解存储库指令和按路径限定范围的指令文件如何传递给智能体。
- 更新指令文件，确保遵循编码标准。
- 查看指令文件对代码的影响。

## 场景

Tailspin Toys 制定了一系列开发实践指南和要求，包括：

- 注释应解释意图和不明显的决策，而不是复述代码。
- `db/` 和 `src/lib/` 中导出的函数应使用 TSDoc/JSDoc 说明用途、参数和返回值，包括适用时可注入的 `db` 参数。
- 可复用的 Astro 组件应说明其 `Props` 接口；相关代码更改时，注释也应保持更新。
- 保留现有格式和 lint 指南。

通过指令文件，可以让 Copilot 获取正确的信息，并按照这些实践执行任务。

## 指令文件

自定义指令可向 Copilot 提供上下文和偏好，帮助它理解你的编码风格和要求。你可以指定编码约定、库以及希望在代码中添加的注释类型。指令既可以适用于整个存储库，也可以针对特定文件类型提供指导。

指令文件有两种类型：

- `.github/copilot-instructions.md`：每次针对该存储库向 Copilot 提交请求时，都会发送此单一文件。它应包含与大多数请求相关的项目级信息。
- `.github/instructions/*.instructions.md`：可针对具体语言、文件类型或任务提供指导。

> [!NOTE]
> 其他指令格式及其支持情况因环境而异。依赖某种格式前，请查看[自定义指令支持参考][custom-instructions-support]。

## 浏览本项目的自定义指令文件

起始项目中已包含一组指令文件。更改前先浏览现有内容，以便了解更新后的影响。

1. 返回 Codespace。
2. 在 Codespaces 编辑器（不是终端）中打开 `.github/copilot-instructions.md`。
3. 浏览文件，注意项目简介和编码指南。此指令适用于本存储库中与 Copilot 的所有交互。
4. 打开 `.github/instructions` 文件夹并浏览其中的文件。你会看到针对 Astro 文件、Drizzle 数据层、测试等内容的指令。
5. 打开 `.github/instructions/unit-tests.instructions.md`。注意顶部的 `applyTo` 字段；它设置了一个 glob，用于决定指令适用于哪些文件。
6. 打开 `.github/instructions/drizzle.instructions.md`，查看其中指向其他指令文件和项目现有文件的链接。这样可以将较大的指令集拆分成更小、可复用的文件，并向 Copilot 提供参考示例。

## 更新指令以符合团队指南

现有文件已经提供了良好起点，但仍有缺漏。现在修改核心 `copilot-instructions.md` 文件，确保新生成的 TypeScript 代码包含 TSDoc 注释。

1. 在 `.github/copilot-instructions.md` 中找到 **Code formatting guidance** 章节，通常位于第 35 行附近。
2. 在该章节末尾添加以下项目符号：

   ```markdown
   - All new TypeScript should contain TSDocs comments for documentation purposes.
   ```

文件会自动保存。

## 应用更新后的指导

Copilot CLI 会在对话启动时加载存储库指令。保存指令更新后，退出并恢复筛选对话，让 Copilot 在保留功能上下文的同时加载新指导。

1. 如果筛选对话仍处于打开状态，请输入 `/exit` 关闭。Copilot CLI 会自动保存对话。
2. 在 `game-filters-cli` 分支的存储库根目录中，恢复已保存的对话：

   ```bash
   copilot --resume
   ```

   如有提示，请选择筛选对话，并确认当前检出的是 `game-filters-cli` 分支。
3. 让 Copilot 应用更新后的指导：

   ```plaintext
   We just updated our instructions and code guidance. Can you please update the code you generated to match that guidance?
   ```

4. 输入 `/diff` 并查看更改的 TypeScript 文件。确认新增的 TSDoc 注释准确说明了代码。

## 总结与后续步骤

你已了解 Copilot CLI 如何从指令文件中获取上下文，并将新的标准应用于功能代码。具体而言，你：

- 了解了存储库指令和按路径限定范围的指令文件如何传递给智能体。
- 更新了指令文件以确保遵循编码标准。
- 查看了指令文件对代码的影响。

接下来，你将[自定义并运行可复用的 quality-checks 技能][next-lesson]，确保一致地运行 lint 和测试。

## 资源

- [为 Copilot CLI 添加自定义指令][instruction-files]
- [自定义指令支持][custom-instructions-support]
- [创建自定义指令的最佳实践][instructions-best-practices]
- [Awesome Copilot：指令文件合集][awesome-copilot]

[instruction-files]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot/add-custom-instructions
[instructions-best-practices]: https://docs.github.com/copilot/concepts/prompting/response-customization#writing-effective-custom-instructions
[awesome-copilot]: https://awesome-copilot.github.com/
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support
[previous-lesson]: ../3-agent-modes/
[next-lesson]: ../5-agent-skills/
