---
title: "演習 4 - カスタムエージェント"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

## カスタムエージェントとは

GitHub Copilot の[カスタムエージェント][custom-agents-concept]を使うと、開発ワークフローの特定のタスクや分野に合わせた AI アシスタントを作成できます。プロジェクトの `.github/agents` フォルダーに Markdown ファイルでエージェントを定義すると、特定の作業を効果的に行うための指示、ベストプラクティス、コーディングパターン、専門知識を Copilot に伝えられます。チームの知識を、[WCAG][wcag] 準拠を確認するアクセシビリティエージェント、安全なコーディングプラクティスに従うセキュリティエージェント、一貫したテストパターンを守るテストエージェントなどとして再利用できます。

カスタムエージェントは、プロジェクトの `.github/agents` フォルダーまたはグローバルな `~/.copilot/agents` にある Markdown ファイルで定義します。各ファイルには、少なくとも `name` と `description` を含む YAML frontmatter と、その後にエージェントの動作、専門知識、指示を記載する Markdown プロンプトが必要です。

### カスタムエージェントと agent skills の違い

カスタムエージェントと [agent skills][agent-skills-concept] には共通点があります。どちらも主に Markdown ファイルで定義し、AI に作業方法を伝えます。わかりやすく区別すると、**カスタムエージェントは作業者、スキルはツール**です。

カスタムエージェントは独自のコンテキストウィンドウを持ち、作業を進めるためにスキルや他のエージェントを調整します。このラボのアクセシビリティカスタムエージェントは、アクセシビリティガイドラインに沿ってサイトをレビューし、更新します。その作業の一部として、pull request ワークフローのスキルやテスト実行・管理のスキルを呼び出すこともできます。

> [!NOTE]
> カスタムエージェントを作成する唯一の正解はありません。AI を使う他の作業と同様に、環境やシナリオに合わせて試し、改善してください。

[custom-agents-concept]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[agent-skills-concept]: https://docs.github.com/copilot/concepts/agents/about-agent-skills
[wcag]: https://www.w3.org/WAI/standards-guidelines/wcag/

## シナリオ

Tailspin Toys は、視覚能力や好みにかかわらず、すべてのユーザーがクラウドファンディングプラットフォームを利用できるよう取り組んでいます。最近、現在のダークテーマはテキストと背景色のコントラストが不十分で、読みづらいという意見が寄せられました。デザインチームはこの問題に対応するため、ユーザーが切り替えられるハイコントラストモードの実装を依頼しました。

アクセシビリティは重要なので、できるだけ早く実装します。カスタムエージェントを使って機能を生成しましょう。

この演習では、次の内容を学習します。

- 既存のアクセシビリティカスタムエージェントを確認する。
- Copilot Chat でアクセシビリティエージェントを使い、ハイコントラストモードを実装する。

## アクセシビリティカスタムエージェントを確認する

アクセシビリティ用のカスタムエージェントがあらかじめ作成されています。Copilot をどのように導くか確認しましょう。

Codespace に戻り、ターミナルを開いて `main` からアクセシビリティ作業用の新しいブランチに切り替えます。演習 3 のフィルター機能 PR とは分けて作業します。

```bash
git checkout main
git pull
git checkout -b accessibility-vscode
```

1. `.github/agents/accessibility.md` を開きます。
2. `name` と `description` を含む YAML frontmatter を確認します。

> [!CAUTION]
> カスタムエージェントには `name` と `description` を含む frontmatter が必要です。

3. 続くセクションを読み、アクセシブルな Web サイト向けコード生成の責務、アクセシビリティのベストプラクティス、HTML・CSS・JavaScript のコード例、よくある問題を確認します。

## Copilot Chat でカスタムエージェントを使う

VS Code の Copilot Chat ビュー下部にあるエージェントドロップダウンには、`.github/agents` で定義されているカスタムエージェントが表示されます。カスタムエージェントを選ぶと、その指示とツールを使って会話できます。

> [!TIP]
> **Copilot Chat を開く**
>
> 次の手順を始める前に Codespace に戻り、Copilot Chat パネルを開いて **New Chat** を選択します。モードとモデルの選択は演習によって異なるため、該当する手順で指定します。

1. Chat ビューのエージェントドロップダウンで、まだ選択されていない場合は **Agent** を選びます。

   ![Chat ビューのエージェントピッカーを示すスクリーンショット。](../../../_images/shared-chat-mode-selector.png)

2. Chat ビューの下部にあるエージェントドロップダウンを選択します。ここには既定のエージェント **default** が表示されています。
3. 利用可能なエージェントから **Accessibility agent** を選択します。
4. 次のプロンプトをアクセシビリティエージェントに送信します。

   ```plaintext
   Add a high-contrast mode to the site. There should be a toggle for high contrast which the user can set, and the setting should persist across page reloads using local storage on the browser.
   ```

5. Copilot Chat がコードベースを調べ、変更を提案してプロジェクトのファイルを編集します。編集内容は、ファイルパスと差分とともにチャット内に表示されます。
6. エージェントが変更した作業ファイルの数に合わせて **Files changed** の表示が更新されます。

> [!NOTE]
> この処理には数分かかることがあります。Copilot は Astro コンポーネント、CSS、関連テストなどの実際のファイルを変更します。
>
> 進行中の作業のレビューと指示は次の演習で行います。

## まとめと次のステップ

特定のタスクや分野に対応する専門的な AI アシスタントとして、GitHub Copilot の[カスタムエージェント][custom-agents]を確認しました。カスタムエージェントを使うと、チームの知識や標準を再利用し、Copilot の作業を導けます。

このレッスンでは、カスタムエージェントの定義方法と、Copilot Chat の agent mode で使用する方法を確認しました。次は、同じセッションの変更をレビューし、[エージェントの作業を監視して調整します][next-lesson]。

## リソース

- [カスタムエージェントについて][custom-agents]
- [IDE でカスタムエージェントを作成する][creating-custom-agents-ide]
- [VS Code のカスタムエージェント][custom-agents-vscode]
- [カスタムエージェントの構成][custom-agents-config]
- [awesome-copilot のカスタムエージェント][awesome-copilot-agents]

---

| [← 前のレッスン: Playwright MCP server で機能をテストする][previous-lesson] | [次のレッスン: エージェントを監視して管理する →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-mcp/
[next-lesson]: ../5-managing-agents/
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[creating-custom-agents-ide]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/create-custom-agents-in-your-ide
[custom-agents-vscode]: https://code.visualstudio.com/docs/copilot/customization/custom-agents
[custom-agents-config]: https://docs.github.com/copilot/reference/custom-agents-configuration
[awesome-copilot-agents]: https://github.com/github/awesome-copilot/tree/main/agents
