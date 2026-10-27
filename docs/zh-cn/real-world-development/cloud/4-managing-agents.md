---
title: "练习 4 - 监控和管理智能体"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

前两节练习中，你让 Copilot 云智能体处理了三个不同任务，帮助改进用户体验并添加功能。云智能体以异步和自主方式工作，但监控这些任务仍然很重要。

你可以使用多种工具管理分配给云智能体的任务，包括 GitHub.com 上的[智能体页面][agents-page]。在这个控制面板中，可以查看所有已创建开放拉取请求 (PR) 的智能体任务，了解它执行的操作，还可以引导正在运行的会话。

本课将介绍如何：

- 浏览智能体页面，监控云智能体任务。
- 引导正在进行的会话，让智能体添加新功能。

## 场景

将高对比度模式任务分配给智能体后，团队意识到也可以顺便添加浅色模式。由于智能体已经在更新网站样式并添加切换功能，因此一并实现浅色模式很合理。现在需要引导智能体，确保它同时添加高对比度模式和浅色模式。

## 查看 Copilot 云智能体任务

先查看分配给 Copilot 云智能体的所有任务的当前状态。

1. 转到 [Copilot 智能体页面](https://github.com/copilot/agents)。
2. 查看主面板和左侧面板中的任务列表。应能看到你分配给 Copilot 的任务，包括：
   - 更新代码文档。
   - 生成用于修改游戏的 API。
   - 为网站添加高对比度模式。
3. 选择一个正在运行的任务，查看 Copilot 已执行的工作。可能包括：
   - 从存储库检出代码。
   - 为 Copilot 创建工作环境。
   - 设置 MCP 服务器。
   - 执行完成任务所需的各项操作。

> [!NOTE]
> 具体显示的步骤因 Copilot 当前的工作状态和执行方式而异。

4. 另请查看右侧的拉取请求窗格，这里显示 PR 和已更改的文件，便于进一步监控。

## 引导云智能体

现在你已查看正在进行的任务，可以让 Copilot 在实现高对比度模式时也添加浅色模式。

1. 选择与添加高对比度模式相关的会话。具体标题会因 Copilot 使用的名称和当前工作状态而异。

   ![控制面板中的无障碍会话](../../../_images/ex6-accessibility-session.png)

2. 观察会话几分钟，直到 Copilot 完成准备工作并开始处理任务。出现类似下方的消息时，就说明它已开始工作。
3. 在 **Steer active session while Copilot is working** 对话框中，输入以下提示词：

   ```plaintext
   While we are working on a high contrast mode, let's also add a light mode. There should be a switch for this mode as well where users can select their desired display mode.
   ```

   ![Copilot 智能体任务页面截图，其中高亮了 Steer active session while Copilot is working 对话框](../../../_images/ex6-steer-cloud-agent-task.png)

4. 按 <kbd>Enter</kbd> 发送提示词。
5. 注意 Copilot 会确认收到提示词，并将其纳入工作流程。

## 等待 Copilot 完成

和之前一样，Copilot 会继续处理更新后的任务。收到提示后，它会先完成当前步骤，然后将新要求加入工作流程。

这需要几分钟，可以利用这段时间回顾目前学到和探索的内容。

## 总结与后续步骤

本课介绍了 Copilot 智能体页面，这是监控和引导 GitHub Copilot 云智能体任务的中心位置。在这个控制面板中，可以跟踪所有正在进行和已完成的任务、审查已执行的工作，还可以调整正在运行任务的范围或提供更多指导。

本课介绍了以下内容：

- 使用智能体控制面板和智能体页面监控云智能体任务。
- 重定向正在运行的会话，让智能体添加新功能。

Copilot 正在完成无障碍功能。接下来[迭代改进 Copilot 创建的拉取请求][next-lesson]。

## 资源

- [Copilot 智能体页面][agents-page]
- [关于自定义智能体][custom-agents]

---

| [← 上一课：自定义智能体][previous-lesson] | [下一课：迭代改进 Copilot 的工作 →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-custom-agents/
[next-lesson]: ../5-iterating/
[agents-page]: https://github.blog/changelog/2025-07-03-agents-page-for-copilot-coding-agent-in-public-preview
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
