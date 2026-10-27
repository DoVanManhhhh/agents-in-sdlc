---
title: "演習 3 - カスタムエージェント"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

## カスタムエージェントとは

GitHub Copilot の[カスタムエージェント][custom-agents-concept]を使うと、開発ワークフローの特定のタスクや分野に合わせた AI アシスタントを作成できます。プロジェクトの `.github/agents` フォルダーに Markdown ファイルでエージェントを定義すると、特定の作業を効果的に行うための指示、ベストプラクティス、コーディングパターン、専門知識を Copilot に伝えられます。チームの知識を、[WCAG][wcag] 準拠を確認するアクセシビリティエージェント、安全なコーディングに従うセキュリティエージェント、一貫したテストパターンを守るテストエージェントなどとして再利用できます。

カスタムエージェントは、プロジェクトの `.github/agents` またはグローバルな `~/.copilot/agents` にある Markdown ファイルで定義します。各ファイルには、少なくとも `name` と `description` を含む YAML frontmatter と、その後にエージェントの動作、専門知識、指示を記載する Markdown プロンプトが必要です。

### カスタムエージェントと agent skills の違い

カスタムエージェントと [agent skills][agent-skills-concept] には共通点があります。どちらも主に Markdown ファイルで定義し、AI に作業方法を伝えます。わかりやすく区別すると、**カスタムエージェントは作業者、スキルはツール**です。

カスタムエージェントは独自のコンテキストウィンドウを持ち、作業を進めるためにスキルや他のエージェントを調整します。このラボのアクセシビリティカスタムエージェントは、アクセシビリティガイドラインに沿ってサイトをレビューして更新します。その作業の一部として、pull request ワークフローのスキルやテスト実行・管理のスキルを呼び出すこともできます。

> [!NOTE]
> カスタムエージェントを作成する唯一の正解はありません。AI を使う他の作業と同様に、環境やシナリオに合わせて試し、改善してください。

[custom-agents-concept]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[agent-skills-concept]: https://docs.github.com/copilot/concepts/agents/about-agent-skills
[wcag]: https://www.w3.org/WAI/standards-guidelines/wcag/

カスタムエージェントを使って、次の内容を確認します。

- カスタムエージェントの定義方法。
- タスクをカスタムエージェントに割り当てる方法。

## シナリオ

Tailspin Toys は、視覚能力や好みにかかわらず、すべてのユーザーがクラウドファンディングプラットフォームを利用できるよう取り組んでいます。現在のダークテーマはテキストと背景色のコントラストが不十分で、読みづらいという意見が寄せられました。デザインチームは、ユーザーが切り替えられるハイコントラストモードの実装を依頼しました。

アクセシビリティは重要なので、カスタムエージェントを使って迅速に機能を実装します。

## アクセシビリティカスタムエージェントを確認する

アクセシビリティ用のカスタムエージェントがあらかじめ作成されています。Copilot をどのようにガイドするかを確認します。

Codespace に戻り、アクセシビリティカスタムエージェントのファイルを確認します。

1. `.github/agents/accessibility.md` を開きます。
2. `name` と `description` を含む YAML frontmatter を確認します。

> [!CAUTION]
> カスタムエージェントには `name` と `description` を含む frontmatter が必要です。

3. 続くセクションを読み、アクセシブルな Web サイト向けコード生成の責務、アクセシビリティのベストプラクティス、HTML・CSS・JavaScript のコード例、よくある問題を確認します。

## Issue を作成して割り当てる

Mission control は、この環境のエージェントを管理する場所です。Copilot cloud agent にタスクを割り当て、進行状況を監視し、追加の指示を送れます。まず、ハイコントラストモードの作成を Copilot に依頼します。

1. リポジトリを開きます。
2. **Issues** タブを選択します。
3. **New issue** を選択して新しい Issue の画面を開きます。
4. **Blank issue** を選択します。
5. **Title** に `Add high contrast mode to website` と入力します。
6. **Description** に次の内容を入力します。

   ```plaintext
   We need a high contrast mode for the site. There should be a toggle for high contrast which the user can set. It should store the setting in local storage on the browser.
   ```

7. **Create** を選択して Issue を作成します。
8. 右側の **Assign to Copilot** を選択して割り当て画面を開きます。
9. カスタムエージェントの一覧から **Accessibility agent** を選択します。

   ![カスタムエージェントの割り当て画面で Accessibility agent が選択されているスクリーンショット](../../../_images/ex5-select-custom-agent.png)

10. **Assign** を選択します。
11. Copilot はバックグラウンドでタスクを開始します。

## まとめと次のステップ

特定のタスクや分野に対応する専門的な AI アシスタントとして、GitHub Copilot の[カスタムエージェント][custom-agents]を確認しました。カスタムエージェントを使うと、チームの知識や標準を再利用し、Copilot の作業を導けます。

このレッスンでは、カスタムエージェントの定義方法と、タスクをエージェントに割り当てる方法を学びました。Copilot がハイコントラストモードを実装している間に、[Mission control でセッションを監視して指示します][next-lesson]。

## リソース

- [カスタムエージェントについて][custom-agents]
- [Organization でカスタムエージェントを使うための準備][org-custom-agents]
- [Enterprise でカスタムエージェントを使うための準備][enterprise-custom-agents]

---

| [← 前のレッスン: GitHub Copilot cloud agent][previous-lesson] | [次のレッスン: エージェントの監視と管理 →][next-lesson] |
|:--|--:|

[previous-lesson]: ../2-cloud-agent/
[next-lesson]: ../4-managing-agents/
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[org-custom-agents]: https://docs.github.com/copilot/how-tos/administer-copilot/manage-for-organization/prepare-for-custom-agents
[enterprise-custom-agents]: https://docs.github.com/copilot/how-tos/administer-copilot/manage-for-enterprise/manage-agents/prepare-for-custom-agents
