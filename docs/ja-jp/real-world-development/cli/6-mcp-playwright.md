---
title: "レッスン 6 - Playwright MCP で機能を検証する"
description: "Copilot CLI の Playwright MCP を確認または設定して、ブラウザーでフィルター機能を操作します。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

コードを書くこと以外にも、データや外部サービスを扱い、Copilot が使える自動化機能を増やす必要があります。そこで役立つのが MCP server です。MCP server を使うと、Copilot CLI に組み込まれていないツールやサービスを利用できます。

このレッスンでは、次の内容を学習します。

- Model Context Protocol (MCP) と Copilot CLI での利用方法を理解する。
- まだ利用できない場合は Playwright MCP server を追加する。
- エージェントにブラウザーを操作させ、フィルター機能を確認する。

## シナリオ

単体テストや E2E テストは重要ですが、UI の変更を検証するには、実際に UI を操作する必要があります。Copilot がユーザーと同じように開発中のサイトを使えるようにし、期待どおりに動作するかを確かめます。

## Model Context Protocol (MCP) とは

[Model Context Protocol (MCP)][mcp-blog-post] は、AI エージェントが外部のツールやサービスと通信するための仕組みです。MCP を使うと、エージェントは最新の情報にアクセスしたり、ユーザーに代わって操作を実行したりできます。

ツールやリソースへのアクセスは、AI エージェントと外部サービスをつなぐ MCP server を通じて行います。各 MCP server は、エージェントが利用できる異なるツールやリソースを提供します。

よく使われている MCP server の例を紹介します。

- **[GitHub MCP Server][github-mcp]**: GitHub リポジトリ、Issue、pull request を管理する API を利用できます。
- **[Playwright MCP Server][playwright-mcp-server]**: Playwright を使ったブラウザー自動化機能を利用できます。

ほかにも多くの MCP server が公開されています。GitHub は、エコシステム内の MCP server を見つけやすくし、貢献を促進するために [MCP registry][mcp-registry] をホストしています。

> [!CAUTION]
> MCP server は、プロジェクト内の他の依存関係と同様に扱ってください。使用前にソースコードを確認し、公開元を検証し、セキュリティへの影響を考慮してください。

## Playwright MCP server を追加する

Playwright MCP server がまだ利用できない場合は追加し、Copilot がユーザーと同じようにサイトを操作できるようにします。

> [!NOTE]
> Playwright MCP が Copilot CLI にすでに設定されている場合は、セットアップを飛ばして次のセクションに進みます。

1. Codespace に戻ります。
2. Copilot CLI で次のコマンドを入力し、MCP server の追加画面を開きます。

   ```plaintext
   /mcp add
   ```

3. 名前に `playwright` と入力し、<kbd>Tab</kbd> を押します。
4. <kbd>Enter</kbd> を押して server の種類に **STDIO** を指定し、<kbd>Tab</kbd> を押します。
5. **Command** ダイアログに次の内容を貼り付けます。

   ```plaintext
   npx -y @playwright/mcp@latest --headless --no-sandbox
   ```

6. <kbd>Control</kbd>+<kbd>S</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>S</kbd> (Windows/Linux) を押して、新しい MCP server を保存します。
7. <kbd>Esc</kbd> を押して MCP ダイアログを閉じます。

## Playwright で機能を確認する

以前は手動で機能を確認しました。次は、Copilot で利用できる Playwright MCP server を使って同じように確認します。

1. 次のプロンプトを使い、Copilot に Playwright MCP server で機能を検証するよう依頼します。

   ```plaintext
   Start the app and use Playwright MCP to check filtering against the issue and our plan. Tell me what works and what doesn't, without making changes. Stop the server you started when you're done.
   ```

> [!NOTE]
> 通常、Copilot は指示しなくても MCP server を見つけて使います。使用する server がわかっている場合は、プロンプトで示すと動作をより一貫させられ、トークンも節約できます。

2. Copilot がブラウザーで実行する各手順を確認します。
3. 報告を読み、すべてが期待どおりに動作することを確かめます。

Copilot はサーバーを起動し、Playwright でサイトを操作してからサーバーを停止し、結果を報告します。

## まとめと次のステップ

Copilot CLI から Playwright MCP server を使って、実際のブラウザーで機能を確認しました。このレッスンでは、MCP の仕組みと Copilot CLI での使い方を学び、必要に応じて Playwright MCP server を追加し、エージェントにブラウザーを操作させました。

次は、スキルとブラウザーツールを組み合わせる [QA カスタムエージェントを作成します][next-lesson]。

## リソース

- [MCP とは何か、なぜ注目されているのか][mcp-blog-post]
- [Microsoft Playwright MCP Server][playwright-mcp-server]
- [Copilot CLI に MCP server を追加する][add-mcp]

[previous-lesson]: ../5-agent-skills/
[next-lesson]: ../7-qa-agent/
[mcp-blog-post]: https://github.blog/ai-and-ml/llms/what-the-heck-is-mcp-and-why-is-everyone-talking-about-it/
[playwright-mcp-server]: https://github.com/microsoft/playwright-mcp
[github-mcp]: https://github.com/github/github-mcp-server
[mcp-registry]: https://github.com/mcp
[add-mcp]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot/add-mcp-servers
