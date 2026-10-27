---
title: "练习 9 - GitHub Copilot CLI 斜杠命令"
description: "探索管理上下文、选择模型、共享会话和委派给云智能体的斜杠命令。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

与其他优秀的 CLI 工具一样，GitHub Copilot CLI 提供了许多斜杠命令。这些命令可以调用高级功能、查看内部信息或使用其他配置选项。你已经使用过 `/diff`、`/mcp`、`/skills`、`/agent` 和 `/pr` 等命令。接下来探索其他一些实用命令。

本课将介绍如何：

- 使用 `/context` 和 `/compact` 了解 Copilot 如何管理对话上下文。
- 使用 `/model` 查看可用模型。
- 了解 `/share` 如何导出或共享会话。
- 探索用于并行工作、工作树和委派给云智能体的可选命令。

## 场景

核心 CLI 工作流已完成。现在探索一些其他功能：管理上下文、切换模型、共享会话，以及选择是否将工作委派给 [Copilot 云智能体][about-cloud-agent]。

## 查看 Copilot CLI 上下文

处理较大或较复杂的任务时，可能会达到模型上下文窗口的上限。Copilot CLI 会在需要时自动压缩对话；你也可以使用斜杠命令查看或手动压缩上下文。

1. 返回 Codespace；如果 Copilot CLI 尚未打开，请从存储库根目录启动。
2. 输入：

   ```plaintext
   /context
   ```

3. 注意模型、当前 token 用量，以及上下文在系统指令、工具、消息和剩余空间之间的分布。
4. 压缩对话：

   ```plaintext
   /compact
   ```

5. 再次输入 `/context` 并比较结果。如果对话本来就很短，变化可能并不明显。

> [!NOTE]
> 上下文窗口接近填满时，Copilot CLI 会自动压缩。想自行决定何时压缩时，可使用 `/compact`。如果要切换到无关任务并开始全新对话，请使用 `/clear` 或 `/new`。

## 选择模型

不同模型有不同的优势，不同开发者也有各自的偏好。Copilot CLI 允许你查看并选择要使用的模型。

1. 输入：

   ```plaintext
   /model
   ```

2. 查看可用模型和用量信息。
3. 保留当前模型、选择其他模型，或按 <kbd>Esc</kbd> 关闭列表。

## 共享会话

团队成员一起工作并分享经验，可以帮助彼此更好地使用 AI 工具。`/share` 命令可以将会话导出为 Markdown 或 HTML 文件、创建可共享的链接，或发布为 GitHub gist。

1. 输入 `/help`，查看当前安装版本中 `/share` 的选项。
2. 如果要共享此会话，请选择适合的目标，例如 `/share file`，将其导出为本地 Markdown 文件。
3. 发送或发布导出内容前先检查内容。会话导出可能包含提示词、回复和项目细节。

发布链接或 gist 是可选操作。不要发布团队无意共享的存储库或对话内容。

## 可选：扩展并行工作或委派任务

核心工作坊已完成。Copilot CLI 还提供了适用于较大任务的命令：

- `/fleet` 可以将独立子任务交给多个子智能体并行执行。
- `/worktree` 可以为单独的任务创建隔离的 Git 工作树。
- `/delegate` 可以将任务交给 GitHub Copilot 云智能体；它会异步处理任务，并可能创建拉取请求。

这些命令是可选的，因为它们可能创建额外的工作树或远程任务。开始前先创建一个范围明确的新任务，并按常规流程审查结果。想深入了解异步智能体工作，可继续学习[云智能体工作坊][cloud-workshop]。

## 总结与后续步骤

使用 Copilot CLI 的斜杠命令，可以进行配置、共享会话并查看内部工作情况。本课中，你：

- 使用 `/context` 和 `/compact` 了解 Copilot 如何管理对话上下文。
- 使用 `/model` 查看可用模型。
- 了解 `/share` 如何导出或共享会话。
- 探索了用于并行工作、工作树和委派给云智能体的可选命令。

Copilot CLI 还有更多斜杠命令和功能值得探索。最后，[回顾已学内容][next-lesson]并了解后续学习方向。

## 资源

- [Copilot CLI 命令参考][cli-reference]
- [Copilot CLI 中的上下文管理][context-management]
- [关于 Copilot 云智能体][about-cloud-agent]

[previous-lesson]: ../8-create-pull-request/
[next-lesson]: ../10-review/
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[context-management]: https://docs.github.com/copilot/concepts/agents/copilot-cli/context-management
[about-cloud-agent]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-workshop]: ../../cloud/
