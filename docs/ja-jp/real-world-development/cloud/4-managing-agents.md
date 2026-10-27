---
title: "演習 4 - エージェントの監視と管理"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

前の2つの演習では、Copilot cloud agent にユーザー体験の改善と機能追加に関する3つのタスクを依頼しました。cloud agent は非同期かつ自律的に作業しますが、タスクの進行状況を監視することも重要です。

cloud agent に割り当てたタスクを管理するツールはいくつかあります。[GitHub.com の agents ページ][agents-page]もその1つです。この Mission control では、オープンな pull request (PR) があるすべてのエージェントタスクを確認できます。実行内容を調べ、進行中のセッションに追加の指示を送ることもできます。

このレッスンでは、次の内容を学習します。

- agents ページを使って cloud agent のタスクを監視する。
- 進行中のセッションに指示を送り、機能を追加する。

## シナリオ

ハイコントラストモードの作成をエージェントに依頼した後、チームはライトモードも追加することにしました。サイトのスタイルと切り替え機能を更新しているため、同時に実装するのが合理的です。エージェントにライトモードも追加するよう指示します。

## Copilot cloud agent のタスクを確認する

Copilot cloud agent に割り当てたタスクの現在の状態を確認します。

1. [Copilot agents ページ](https://github.com/copilot/agents)を開きます。
2. メインペインと左ペインの両方にタスク一覧が表示されます。Copilot に割り当てた次のタスクなどを確認します。
   - コードのドキュメントの更新。
   - ゲーム変更用 API の生成。
   - Web サイトへのハイコントラストモードの追加。
3. 実行中のタスクを選択し、Copilot が実行した手順を確認します。たとえば、リポジトリのチェックアウト、作業環境の作成、MCP server の設定、タスク完了に向けた各種操作が表示されます。

> [!NOTE]
> 表示される手順は、Copilot の進行状況や作業方法によって異なります。

4. 右側に表示される PR ペインで、pull request と変更ファイルを確認できます。

## cloud agent に追加の指示を送る

実行中のタスクを確認したので、ハイコントラストモードの作業中にライトモードも追加するよう Copilot に依頼します。

1. ハイコントラストモードを追加するセッションを選択します。タイトルは Copilot が付けた名前や作業状況によって異なります。

   ![Mission control に表示されるアクセシビリティのセッション](../../../_images/ex6-accessibility-session.png)

2. セットアップが完了し、作業が始まったことを示すメッセージが表示されるまで、数分間セッションを確認します。
3. **Steer active session while Copilot is working** ダイアログに次のプロンプトを入力します。

   ```plaintext
   While we are working on a high contrast mode, let's also add a light mode. There should be a switch for this mode as well where users can select their desired display mode.
   ```

   ![agents ページの cloud agent タスクで、Copilot の作業中にセッションへ指示を送るダイアログを示したスクリーンショット](../../../_images/ex6-steer-cloud-agent-task.png)

4. <kbd>Enter</kbd> を押してプロンプトを送信します。
5. Copilot がプロンプトを受け取り、作業計画に追加したことを確認します。

## Copilot に作業を続けさせる

Copilot は更新されたタスクに取り組みます。メッセージを送信した時点で実行中だった手順が終わると、新しい依頼を作業に取り込みます。

処理には数分かかります。その間に、これまでに学んだ内容を振り返りましょう。

## まとめと次のステップ

GitHub Copilot cloud agent のタスクを監視して指示するための中心的な場所である Copilot agents ページを確認しました。Mission control では、実行中および完了したタスクを追跡し、作業内容をレビューして、進行中のタスクに追加の指示を送れます。

このレッスンでは、agents ページでタスクを監視し、進行中のセッションに追加の機能を依頼しました。Copilot がアクセシビリティ機能を実装している間に、次は[作成された pull request を反復して改善します][next-lesson]。

## リソース

- [Copilot agents ページ][agents-page]
- [カスタムエージェントについて][custom-agents]

---

| [← 前のレッスン: カスタムエージェント][previous-lesson] | [次のレッスン: Copilot の作業を反復する →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-custom-agents/
[next-lesson]: ../5-iterating/
[agents-page]: https://github.blog/changelog/2025-07-03-agents-page-for-copilot-coding-agent-in-public-preview
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
