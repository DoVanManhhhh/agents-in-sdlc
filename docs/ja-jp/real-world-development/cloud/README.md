---
slug: ja-jp/real-world-development/cloud
title: "GitHub Copilot cloud agent"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

**[GitHub Copilot cloud agent](https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent)** を使うと、GitHub Copilot がクラウド上で非同期に作業できます。GitHub でタスクを割り当てると、cloud agent がバックグラウンドでリポジトリを調べて変更を行い、pull request を作成します。その間、別の作業を続けられます。

この演習では、cloud agent が従うカスタム指示を追加し、GitHub Issue を割り当てて実装を依頼します。カスタムエージェントを確認して利用し、エージェントのダッシュボードからセッションを監視して指示を追加します。最後に、作成された pull request をレビューし、結果を反復して改善します。

## 演習

| 演習 | トピック | 説明 |
|----------|-------|-------------|
| [0. 前提条件][ex0] | セットアップ | リポジトリと Codespace を作成する |
| [1. カスタム指示][ex1] | コンテキスト | cloud agent が従うカスタム指示を追加する |
| [2. Cloud Agent][ex2] | 非同期エージェント | Issue を Copilot cloud agent に割り当てる |
| [3. カスタムエージェント][ex3] | 専門エージェント | カスタムエージェントを確認して使う |
| [4. エージェントの管理][ex4] | 監視 | エージェントのセッションを監視して指示する |
| [5. 反復][ex5] | レビュー | PR をレビューし、Copilot の作業を反復して次の手順を選ぶ |

## 前提条件

このワークショップに参加する前に、次のものを用意してください。

- [ ] 有効な **Copilot Student、Pro、Pro+、Business、Enterprise** プランがある GitHub アカウント
- [ ] アカウントまたは Organization で Copilot cloud agent が有効になっていること

> [!TIP]
> 有料プランがない場合、認証済みの学生は [GitHub Education][callout-student-plan-education] を通じて GitHub Copilot を無料で利用できます。**Copilot Student** プランには、このワークショップで使うエージェント、MCP、コードレビュー、Copilot CLI の機能が含まれています。

[callout-student-plan-education]: https://github.com/education/students

> [!NOTE]
> Cloud agent は Copilot Free を除く **Copilot Student、Pro、Pro+、Business、Enterprise** で利用できます。Copilot Business または Enterprise では、管理者が Organization で有効にする必要があります。

> [!NOTE]
> このワークショップでは MCP を扱いません。Copilot で MCP server を使う方法は、[CLI の演習][cli-harness]または [VS Code の演習][vscode-harness]を確認してください。

## はじめる

**[演習 0: 前提条件から始める →][ex0]**

[ex0]: 0-prerequisites/
[ex1]: 1-custom-instructions/
[ex2]: 2-cloud-agent/
[ex3]: 3-custom-agents/
[ex4]: 4-managing-agents/
[ex5]: 5-iterating/
[cli-harness]: ../cli/
[vscode-harness]: ../vscode/
