---
title: "レッスン 8 - 機能の PR を作成してマージする"
description: "フィルター機能、指示、スキルの更新、QA プロファイル、テストをまとめてレビューし、PR を作成して Agent Merge を使用します。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

フィルター機能の実装、指示とスキルの更新、品質保証 (QA) プロファイル、テストを1つのブランチに保存しました。すべてをまとめてレビューし、pull request を作成します。星評価の pull request (PR) は手動でマージしましたが、今回は **Agent Merge** にプロセスの管理を任せます。

> [!NOTE]
> 通常は、機能、指示の更新、スキルの更新、QA エージェントを複数の PR に分けます。ワークショップを簡潔にするため、フィルター機能と品質に関するワークフロー全体を1つの会話とブランチで進め、この PR にまとめました。

このレッスンでは、次の内容を学習します。

- Agent Merge と、マージのライフサイクルを自動化する仕組みを理解する。
- 機能の変更全体と検証の証拠を確認する。
- フィルター機能の PR を作成する。
- レビュー後にのみ Agent Merge を有効にし、PR がマージされたことを確認する。

## シナリオ

フィルター機能のワークフロー全体を通じ、Copilot で機能を計画、実装、検証しました。Tailspin Toys では、マージの承認を開発者の管理下に置いたまま、残りの PR 作業を自動化したいと考えています。

## Agent Merge とは

**Agent Merge** は pull request のマージに必要な残りの作業を自動化します。有効にすると、Copilot は PR を妨げているもの (失敗した継続的インテグレーション (CI) チェックの修正、レビューコメントへの対応、必要なリベースなど) に対処し、リポジトリが許可していれば GitHub の自動マージを有効にします。

ここまでは自分で **Merge pull request** を選択していました。Agent Merge にその作業を任せられますが、有効にする前に作業をレビューし、準備ができていることを確認してください。

## Agent Merge で PR を管理する

コードの作成が終わったら、全体をレビューし、PR を作成して、残りの作業を Agent Merge に任せます。

1. Codespace に戻ります。
2. Copilot CLI で `/agent` を入力し、エージェントダイアログを開きます。
3. **Default** を選択し、<kbd>Enter</kbd> を押します。
4. `/pr create` コマンドを実行して PR を作成します。
5. `/pr agentmerge` を実行して Agent Merge を有効にします。
6. Copilot が PR の継続的インテグレーションを確認します。すべて成功すると、マージを実行します。
7. Copilot が「PR #14 was squash-merged successfully.」などのメッセージを表示することを確認します。

> [!IMPORTANT]
> Agent Merge は、必須の承認、ブランチ保護、マージキュー、リポジトリ設定、権限の不足を回避しません。処理がブロックされた場合は報告内容を確認し、リポジトリで許可されているときは、内容をレビューして手動でマージしてください。

## まとめと次のステップ

コードの生成、テストと検証、pull request のプロセスなど、開発プロセスの複数の部分を自動化しました。このレッスンでは、Agent Merge の概要を学び、機能の変更と検証の証拠を確認し、レビュー後に Agent Merge を有効にして PR のマージを確認しました。

次は、コンテキスト、モデル、共有、任意のクラウドへの委任に使える[スラッシュコマンドを確認します][next-lesson]。

## リソース

- [Copilot CLI で pull request を管理する][manage-prs]
- [Copilot CLI コマンド リファレンス][cli-reference]

[previous-lesson]: ../7-qa-agent/
[next-lesson]: ../9-cli-power-tools/
[manage-prs]: https://docs.github.com/copilot/how-tos/copilot-cli/use-copilot-cli/manage-pull-requests
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
