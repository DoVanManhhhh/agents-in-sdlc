---
title: "演習 3 - Playwright MCP server で機能をテストする"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 前のレッスン: Agent mode][previous-lesson] · [次のレッスン: カスタムエージェント →][next-lesson]

agent mode でフィルター機能を作成しました。pull request を開く前に、ブラウザーで正しく動作することを確認します。自分でアプリを操作する代わりに、**Playwright MCP server** を接続し、Copilot に実際のブラウザーを操作させて機能をテストします。その後、ブランチを公開して PR を作成します。

この演習では、次の内容を学習します。

- Model Context Protocol (MCP) と MCP server が Copilot にツールを追加する仕組み。
- Playwright MCP server をワークスペースに追加する方法。
- Copilot に Playwright MCP server を使わせ、ブラウザーでフィルター機能を手動テストする方法。
- フィルター機能のブランチを公開し、pull request を作成する方法。

## Model Context Protocol (MCP) とは

agent mode は、エディターの外部にある機能を利用すると、さらに便利になります。Copilot が外部のツールやサービスと通信する標準的な方法が Model Context Protocol (MCP) です。

![agent mode の内部構成と、MCP server や VS Code 拡張機能が提供するツールを含むコンテキスト、LLM、ツールとのやり取りを示す図](../../../_images/ex1-mcp-diagram.png)

[Model Context Protocol (MCP)](https://github.blog/ai-and-ml/llms/what-the-heck-is-mcp-and-why-is-everyone-talking-about-it/) を使うと、AI エージェントは外部のツールやサービスと通信できます。リソースを使って最新情報にアクセスしたり、ツールを使ってユーザーに代わって操作を実行したりできます。

これらのツールやリソースには、AI エージェントと外部サービスをつなぐ MCP server を通じてアクセスします。MCP server は、既存の API や npm パッケージなどのローカルツールとエージェント間の通信を管理します。各 server は、エージェントが利用できるツールやリソースを提供します。

よく使われている MCP server の例を紹介します。

- **[GitHub MCP Server](https://github.com/github/github-mcp-server)**: GitHub リポジトリを管理する API を利用できます。リポジトリの作成、更新、Issue や pull request の管理などをエージェントが実行できます。
- **[Playwright MCP Server](https://github.com/microsoft/playwright-mcp)**: Playwright によるブラウザー自動化機能を利用できます。Web ページの移動、フォームの入力、ボタンの選択などをエージェントが実行できます。

ほかにも多くの MCP server が、さまざまなツールやリソースを提供しています。GitHub は、エコシステム内の MCP server を見つけやすくし、貢献を促進するために [MCP registry](https://github.com/mcp) をホストしています。

> [!CAUTION]
> セキュリティの観点から、MCP server はプロジェクト内の他の依存関係と同様に扱ってください。使用前にソースコードを確認し、公開元を検証し、セキュリティへの影響を考慮します。信頼できる MCP server のみを使用し、機密情報や操作へのアクセスを許可する際は注意してください。

## MCP の構成を確認する

`.vscode/mcp.json` ファイルで、この VS Code ワークスペースで利用する MCP server を設定します。

1. Codespace で `.vscode/mcp.json` を開きます。
2. `github` server がすでに設定されていることを確認します。

   ```json
   {
     "servers": {
       "github": {
         "type": "http",
         "url": "https://api.githubcopilot.com/mcp/"
       }
     }
   }
   ```

`github` の設定はプロジェクトテンプレートに含まれています。そのため、前の演習で Copilot はバックログの Issue を読み取れました。[リモート GitHub MCP server][remote-github-mcp-server]を使うため、ローカルにインストールする必要はありません。VS Code は HTTP で接続し、Copilot が初めてツールを使うときに GitHub で認証します。

## Playwright MCP server を追加する

次に、2つ目の server を追加します。[Playwright MCP server][playwright-mcp-server] を使うと Copilot がブラウザーを操作でき、機能のテストに役立ちます。

1. `.vscode/mcp.json` の `github` と並べて `playwright` の設定を追加し、ファイルを次のようにします。

   ```json
   {
     "servers": {
       "github": {
         "type": "http",
         "url": "https://api.githubcopilot.com/mcp/"
       },
       "playwright": {
         "command": "npx",
         "args": ["@playwright/mcp@latest", "--headless"]
       }
     }
   }
   ```

2. ファイルを保存します。

リモートの `github` server と異なり、`playwright` はローカル server です。VS Code はマシン上で `npx @playwright/mcp@latest` を実行して起動します。`--headless` フラグは Playwright のブラウザーを画面表示なしで実行します。Codespace には表示するデスクトップがないため必要です。

> [!NOTE]
> Tailspin Toys では E2E テストに Playwright をすでに使用しているため、必要なブラウザーもインストール済みの場合がほとんどです。ブラウザーが見つからないと Copilot が報告した場合は、`npx playwright install chromium` を実行させ、再試行します。

## server を起動して信頼する

VS Code は必要に応じて MCP server を起動します。Copilot が初めて server のツールを必要としたときに、VS Code が起動し、信頼するか確認します。

1. `.vscode/mcp.json` の `playwright` 設定の上に **Start** が表示されたら選択し、server を起動して構成を確認します。
2. VS Code が server を信頼するか確認したら、構成を確認し、信頼を選択して起動します。

手動で起動する必要はありません。ここで起動しない場合、次の手順で Copilot がツールを必要としたときに VS Code が起動し、信頼を確認します。

## フィルター機能をテストする

[Playwright MCP server][playwright-mcp-server] から Copilot が操作できるブラウザーを利用できます。自分でサイトを操作しなくても、エージェントがページを開き、移動し、フィルターを適用し、結果を読み取って報告できます。会話を離れずに機能を確認する方法です。

Playwright MCP server はスクリーンショットではなく、ページの[アクセシビリティツリー][playwright-mcp-server]を使います。つまり、エージェントはボタン、リンク、リスト項目などのラベル付き要素を扱います。これは支援技術と同様の情報に基づくため、機能の確認とあわせてアクセシビリティも簡易的に点検できます。

server を接続してアプリを起動したら、次のプロンプトを Copilot に送信してフィルター機能をテストします。

```text
Using the Playwright MCP server, open a browser to the running app at http://localhost:4321 and verify the new game filtering feature:

1. Go to the games page and note how many games are listed.
2. Apply a category filter and confirm the list updates to only show games in that category.
3. Clear it, then apply a publisher filter and confirm the list updates to that publisher.
4. Combine a category and a publisher filter and confirm the results respect both.

Report what you observe at each step, and call out anything that does not behave as expected.
```

Copilot は Playwright MCP server からブラウザーを起動し、各手順を実行して結果を報告します。報告内容を Issue の受け入れ条件に照らし合わせます。問題がある場合は、pull request を作成する前に追加の質問をするか、コードを修正させます。

> [!NOTE]
> このテストには `http://localhost:4321` でアプリが起動している必要があります。開発サーバーを停止した場合は、プロンプトを送る前に再起動します。Playwright MCP server を Copilot が初めて使うときにブラウザーのダウンロードが必要な場合があります。ブラウザーが見つからないと報告されたら、`npx playwright install chromium` を実行させて再試行します。

[playwright-mcp-server]: https://github.com/microsoft/playwright-mcp

## ブランチを公開して pull request を作成する

機能が動作することを確認したので、チームのレビュー用に pull request (PR) を作成します。まず `filtering-vscode` ブランチを公開します。

1. Codespace の **Source Control** パネルに移動し、Copilot が行った変更を確認します。
2. **+** アイコンを選択して変更をステージします。
3. **Sparkle** ボタンを使ってコミットメッセージを生成します。

   ![変更されたファイルを示す Source Control パネルのスクリーンショット](../../../_images/ex3-source-control-changes.png)

4. **Publish** を選択してブランチをリポジトリにプッシュします。

## pull request を作成する

pull request は github.com や GitHub command-line interface (CLI) などから作成できます。GitHub Copilot を使っているので、PR の作成も依頼します。Copilot は関連する Issue を見つけて PR に関連付けられます。

1. Copilot Chat パネルに移動し、**New Chat** を選択します。
2. GitHub のツールを使えるよう、エージェントドロップダウンで **Agent** が選択されていることを確認します。
3. 次のプロンプトで PR の作成を依頼します。

   ```plaintext
   Find the issue in the repo related to filtering by category and publisher. Create a new pull request for the current branch, and associate it with the correct issue.
   ```

4. Copilot が情報を取得したり操作を実行したりする際に、必要に応じて **Continue** を選択して許可します。GitHub ツールを初めて使うときに認証を求められた場合は、画面の指示に従います。
5. Copilot が Issue を検索し、該当するものを見つけて PR を作成する様子を確認します。
6. Copilot が表示したリンクを選択し、PR をレビューします。ただし、まだマージしないでください。

## まとめと次のステップ

MCP と MCP server が Copilot にツールを追加する仕組みを学び、Playwright MCP server をワークスペースに追加しました。ブラウザーからフィルター機能を手動テストしてからブランチを公開し、PR を作成しました。

MCP server を使って機能をテストしましたが、Copilot の拡張方法は MCP だけではありません。次は、アクセシビリティレビューなど、対象を絞ったタスクを効率化する[カスタムエージェントを作成します][next-lesson]。

## リソース

- [MCP とは何か、なぜ注目されているのか][mcp-blog-post]
- [Microsoft Playwright MCP Server][playwright-mcp-server]
- [GitHub MCP Server][github-mcp-server]
- [GitHub MCP Registry][mcp-registry]
- [VS Code の MCP server][vscode-mcp-config]

[previous-lesson]: ../2-agent-mode/
[next-lesson]: ../4-custom-agents/
[mcp-blog-post]: https://github.blog/ai-and-ml/llms/what-the-heck-is-mcp-and-why-is-everyone-talking-about-it/
[github-mcp-server]: https://github.com/github/github-mcp-server
[mcp-registry]: https://github.com/mcp
[remote-github-mcp-server]: https://github.blog/changelog/2025-06-12-remote-github-mcp-server-is-now-available-in-public-preview/
[vscode-mcp-config]: https://code.visualstudio.com/docs/agents/reference/mcp-configuration
