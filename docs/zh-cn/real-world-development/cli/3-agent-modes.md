---
title: "练习 3 - 智能体模式：Plan 和 Autopilot"
description: "使用 Plan 确定方案，使用 Autopilot 根据议题构建筛选功能，再使用 Interactive 模式审查结果。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

我们先为项目添加了一项小功能，但更复杂的更改需要更完善的流程。GitHub Copilot CLI 支持组织现有的工作方式，帮助我们用正确的方法构建所需功能。从本课开始，你将通过几节课遵循典型的智能体驱动开发流程：从议题出发开发新功能，确保代码有效、功能符合预期，最终成功合并到项目中。

> [!NOTE]
> 后续功能工作流会沿用同一对话和分支。通常，不同类型的文件会使用不同分支或 PR；这里会采用简化方式，以便专注于核心概念。

本课将介绍如何：

- 从 GitHub 议题启动新的 Copilot 对话。
- 在 Plan 模式中定义需求。
- 使用 Autopilot 模式实现新功能。
- 审查代码。
- 在转发的浏览器中手动验证功能。

继续开发该功能时，你将更新存储库指令、自定义现有的 `quality-checks` 技能、添加 MCP 验证、创建 QA 智能体并打开功能 PR。

## 场景

Tailspin Toys 的游戏目录不断扩大，访客需要按类别和发行商缩小游戏范围。待办事项中的议题描述了这项功能，但在编码前需要就多个类别如何组合等细节达成共识。你将使用 Plan 模式确定这些决策，然后授权 Autopilot 在明确范围内实现功能。

## 背景

将 AI 编码智能体引入开发流程不会改变基本原则。事实上，这些原则反而更加重要。大多数开发人员遵循类似以下的流程：

1. 从已创建的议题开始，了解要完成的工作。
2. 为需要构建的内容制定计划。
3. 构建并审查代码。
4. 运行测试以验证代码。
5. 手动验证新功能。
6. 创建拉取请求 (PR)。
7. 代码通过审查且持续集成流程成功后，合并代码。

> [!NOTE]
> 具体流程会因团队和组织而异，但大多数都是以上流程的变体。

遵循这种标准流程，可以确保 AI 生成的代码满足既定要求，并经过与手写代码相同的审查。

## 对话模式

**对话模式**控制智能体的自主程度。按 <kbd>Shift</kbd>+<kbd>Tab</kbd> 可在不同模式间切换：

- **Interactive**：你与智能体协同工作。智能体提出更改建议，并等待你的输入后再继续。
- **Plan**：智能体先创建计划，且不能编辑项目文件。
- **Autopilot**：智能体自主编写代码、运行测试并不断迭代，直到认为任务已完成。

先在 Plan 模式中审查计划，再使用 Autopilot 实现。

## 从议题开始

开始筛选功能之前，返回 Codespace 并确认存储库和终端已准备就绪。

1. 返回 Codespace。如果它已停止，请先重新启动。
2. 确认星级评分 PR 已合并。
3. 如果终端尚未打开，请按 <kbd>Control</kbd>+<kbd>\`</kbd>（Mac）或 <kbd>Ctrl</kbd>+<kbd>\`</kbd>（Windows/Linux）。
4. 更新 `main`，然后为筛选功能创建分支：

   ```bash
   git checkout main
   git pull --ff-only
   git checkout -b game-filters-cli
   ```

5. 启动 Copilot CLI：

   ```bash
   copilot --yolo
   ```

6. 按两次 <kbd>Tab</kbd> 打开 **Issues** 选项卡。
7. 按 <kbd>A</kbd> 显示所有议题。
8. 使用方向键选中标题为 **Allow users to filter games by category and publisher** 的议题。
9. 按 <kbd>C</kbd> 将议题添加到提示词中，并返回 **Session** 选项卡。

注意提示词现在以 `#7`（或类似编号）开头。`#` 可将 GitHub 议题或拉取请求 (PR) 加入上下文。

## 规划筛选功能

规划可以让你在交由 Copilot 实施前决定功能的实现方式。对于复杂任务，花些时间规划总是值得的。现在切换到计划模式，并让 Copilot 制定计划。

1. 按 <kbd>Shift</kbd>+<kbd>Tab</kbd> 切换到 Plan 模式。确认提示词下方的模式指示器显示 **Plan**。
2. 在上一步添加的议题引用后输入以下提示词：

   ```plaintext
   Create a plan for implementing this feature.
   ```

Copilot 会开始制定计划：先探索项目，再确定合适的实现方式。

3. Copilot 可能会询问筛选功能的行为。根据自己的偏好回答，没有唯一正确答案。
4. 计划完成后，按 <kbd>Control</kbd>+<kbd>E</kbd>（Mac）或 <kbd>Ctrl</kbd>+<kbd>E</kbd>（Windows/Linux）展开计划。
5. 滚动查看并审查计划。
6. 对不符合你决定的部分，让 Copilot 修改计划。

## 批准 Autopilot

计划编写并审查完成后，就可以实施了。使用 Autopilot 让 Copilot 自行推进任务。

Autopilot 会让 Copilot 持续迭代，直到它认为问题已解决。

1. 选择 **Accept plan and build on autopilot (recommended)**，或所安装版本中名称相近的选项。
2. 确认提示词下方的模式指示器显示 **Autopilot**。
3. 观察 Copilot 如何按照计划生成代码、运行测试并逐步迭代。

> [!NOTE]
> 批准后可能会立即开始实现，因此请先审查计划。如果 Copilot 报告缺少依赖项或端口冲突，应先解决环境设置问题，再认定检查已完成。

## 审查并验证实现

与其他代码一样，生成的代码也需要在合并前审查。下面审查代码并运行站点，确认一切正常。

1. 按 <kbd>Shift</kbd>+<kbd>Tab</kbd> 切换到 Interactive 模式。确认模式指示器不再显示 **Plan** 或 **Autopilot**。
2. 输入 `/diff`，检查筛选功能实现和测试。
3. 对照议题和规划时做出的决定审查结果。
4. 审查完成后，按 <kbd>Esc</kbd> 退出差异视图。
5. 查看项目检查结果，并让 Copilot 修复任何失败项。

## 探索新功能

代码看起来没有问题，但能否正常运行？像之前一样启动应用，并通过 Codespaces 转发端口打开网站。

1. 让 Copilot 启动应用：

   ```plaintext
   Start the app so I can try the filtering feature in my browser. Tell me the URL and leave the server running.
   ```

2. Codespaces 报告端口 `4321` 可用时，选择 **Open in Browser**。
3. 尝试按类别筛选、按发行商筛选，以及按计划商定的组合条件筛选。
4. 确认重置筛选和无匹配结果时的行为符合议题和你的决定。
5. 返回 Codespace，让 Copilot 停止它启动的开发服务器。

## 总结与后续步骤

你已使用不同的对话模式构建并审查功能。本课中，你：

- 从 GitHub 议题启动了新的 Copilot 对话。
- 在 Plan 模式中定义了需求。
- 使用 Autopilot 模式实现了新功能。
- 审查了代码。
- 在转发的浏览器中手动验证了功能。

接下来，你将深入了解代码的生成方式，并[使用自定义指令][next-lesson]确保代码遵循已记录的实践。

## 资源

- [GitHub Copilot CLI 中的 Autopilot][autopilot]
- [Copilot CLI 命令参考][cli-reference]

[autopilot]: https://docs.github.com/copilot/concepts/agents/copilot-cli/autopilot
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[previous-lesson]: ../2-add-star-rating/
[next-lesson]: ../4-custom-instructions/
