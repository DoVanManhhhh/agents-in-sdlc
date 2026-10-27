---
title: "演習 2 - Copilot Agent Mode で機能を追加する"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

小さな更新でも、通常は複数のファイルを変更し、テストを実行する必要があります。開発者は必要なファイルを探して変更し、テストを実行し、問題をデバッグし、更新漏れのファイルを見つけて再度変更します。この作業は何度も続くことがあります。

このようなときに役立つのが Copilot Agent Mode です。

Copilot Agent Mode は、IDE 内でより自律的に作業するように設計されています。開発者と同様に、プロジェクト構成を調べ、必要なファイルを更新し、テストなどのタスクを実行して、見つかった問題を修正します。Agent Mode を使ってサイトに機能を追加する方法を確認しましょう。

> [!NOTE]
> 名前は似ていますが、agent mode と cloud agent は異なる体験を提供します。agent mode は IDE 内で動作し、すばやいフィードバックと対話を可能にします。cloud agent はチームメンバーのように非同期で作業し、Issue や pull request を通じてやり取りします。

この演習では、次の内容を学習します。

- Copilot Agent Mode がプロジェクトを調べ、関連ファイルを特定し、複数の変更を行う方法。
- GitHub Copilot Agent Mode が UI とデータレイヤーにわたって機能を実装する方法。
- コードベースにマージする前に、Copilot Agent Mode が作成した変更とテストをレビューする方法。

## シナリオ

ゲームの一覧が増えてきたため、ユーザーがカテゴリーとパブリッシャーで絞り込めるようにします。前の演習で追加した publishers ヘルパーを使い、残りのデータレイヤー、UI、テストを Copilot Agent Mode で仕上げます。

## Tailspin Toys の Web サイトを実行する

変更を加える前に、Tailspin Toys の現在の機能を確認します。サイトは、開発者をテーマにしたボードゲームのクラウドファンディングプラットフォームです。ゲームの一覧と詳細を表示します。Astro アプリ1つで構成され、ビルド時に静的 HTML を生成します。ページは frontmatter 内で Drizzle ORM を使ってローカルの SQLite データベースに直接クエリを実行します。独立したバックエンド API やクライアントサイドの UI フレームワークはありません。再利用可能なデータアクセスヘルパーは `src/lib/` にあり、インタラクティブな機能は標準 DOM API を使う小規模な Astro `<script>` で追加します。

### Web サイトを起動する

Web サイトを起動するために、`npm run dev` タスクが用意されています。

1. Codespace に戻ります。前の演習の後、`main` に戻っているはずです。
2. Codespace 内で <kbd>Control</kbd>+<kbd>\`</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>\`</kbd> (Windows/Linux) を押してターミナルを開きます。
3. フィルター機能用のブランチを作成して切り替えます。

   ```bash
   git checkout main
   git pull
   git checkout -b filtering-vscode
   ```

4. 次のコマンドを実行して Web サイトを起動します。

   ```bash
   npm run dev
   ```

Astro 開発サーバーが起動すると、次のような URL が表示されます。

```bash
🚀 Tailspin Toys is ready!
   Astro server: http://localhost:4321
   Press Ctrl-C to stop.
```

> [!NOTE]
> `http://localhost:4321` を開くよう求めるダイアログが表示された場合は、**x** を選択して閉じます。

5. ターミナルで <kbd>Command</kbd> (Mac) または <kbd>Ctrl</kbd> (Windows/Linux) を押しながら Astro サーバーの URL `http://localhost:4321` を選択し、Web サイトを開きます。

> [!NOTE]
> Codespace のターミナルで localhost の URL を選択すると、`https://<your-codespace-name>-4321.app.github.dev/` に自動的に転送されます。これは Web サーバーをホストする Codespace へのプライベートトンネルです。

### Web サイトを確認する

Web サイトを開き、主な機能を確認します。

- **ホームページ**: ボードゲームのタイトル、画像、説明を一覧表示します。
- **ゲーム詳細ページ**: ゲームを選択すると、タイトル、説明、パブリッシャー、カテゴリーなどの情報を表示します。

## Copilot でバックログを確認する

> [!TIP]
> **Copilot Chat を開く**
>
> 次の手順を始める前に Codespace に戻り、Copilot Chat パネルを開いて **New Chat** を選択します。モードとモデルの選択は演習によって異なるため、該当する手順で指定します。

サイトは動作しますが、さらに機能を追加します。テンプレートからプロジェクトを作成したときに用意されたバックログを確認します。

1. Chat ビューのエージェントドロップダウンで **Agent** を選択します。Agent は自律的に計画し、複数のファイルを変更し、ターミナルコマンドを実行し、ツールを呼び出します。

   ![Chat ビューのエージェントピッカーを示すスクリーンショット。](../../../_images/shared-chat-mode-selector.png)

2. 利用可能なモデル一覧から **Claude Sonnet 4.5** を選択します。

> [!CAUTION]
> ワークショップの作成者が特定のモデルを推奨するものではありません。ワークショップの作成時に Claude Sonnet 4.5 を使用したため、手順に含めています。提案の一貫性を高めることが目的ですが、LLM の動作は確率的なので、表示される提案が手順と異なる場合があります。これは通常の動作です。

> [!NOTE]
> LLM の確率的な性質により、Copilot は別の MCP コマンドを使う場合がありますが、タスクは完了できるはずです。

3. 次のプロンプトを送信し、バックログについて Copilot に尋ねます。

   ```plaintext
   Please show me the backlog of items from my GitHub repository. Help me prioritize them based on those which will be most useful to the user.
   ```

4. **Continue** を選択して、すべての Issue を一覧表示するコマンドを実行します。
5. 生成された Issue の一覧を確認します。

Copilot がユーザーに最も役立つと思われる項目を優先順位付けしたことを確認します。

## 指示ファイルを確認する

コード生成を依頼する前に、Copilot にコンテキストを与える指示ファイルを確認します。[ユーザーインターフェイス (UI) の指示ファイル][ui-instructions]には、Web サイトの機能追加に関するガイダンスが含まれています。

1. Codespace で `.github/instructions/ui.instructions.md` を開きます。
2. 機能追加に関するガイダンスを確認します。次の内容が含まれます。
   - アーキテクチャの概要。
   - コンポーネント設計、テスト容易性、アクセシビリティの原則。
   - Astro、Tailwind CSS、Drizzle などの指示ファイルへのリンク。

> [!TIP]
> 指示ファイルから別の指示ファイルやプロジェクト内のファイルを参照できます。パスは指示ファイルの場所を基準とするため、ガイダンスを再利用し、大きな指示を管理しやすい単位に分け、Copilot に例やひな型を示せます。

## フィルター機能を実装する

フィルター機能を完成させるには、少なくとも次の3種類の更新が必要です。

- データレイヤー (`src/lib/`) に残りのフィルター処理を追加または調整する。
- フィルター動作のテストを追加または更新する。
- ゲーム一覧ページにフィルター UI を追加する。

コードベースにマージする前にテストを実行して成功させる必要があります。Copilot Agent Mode にこれらのタスクを依頼します。

1. 現在の会話を続けるか、**New Chat** を選択して新しい会話を開始します。
2. **Add Context**、**Instructions**、**ui** の順に選択します。

   ![UI 指示ファイルを選択する例を示すスクリーンショット](../../../_images/ex3-select-instructions-file.png)

3. Chat ビューのエージェントドロップダウンで **Agent** が選択されていることを確認します。

   ![Chat ビューのエージェントピッカーを示すスクリーンショット。](../../../_images/shared-chat-mode-selector.png)

4. モデルが **Claude Sonnet 4.5** のままであることを確認します。
5. 次のプロンプトで、バックログの関連 Issue に基づいて機能を実装するよう Copilot に依頼します。

   ```plaintext
   Please update the site to include filtering by publisher and category based on the requirements from the related GitHub issue in the backlog. A publishers helper already exists from the previous exercise, so preserve and refine that work as needed while completing the remaining data-layer, UI, and tests. Ensure all tests are passing before completion. The server is already running, so you do not need to start it up.
   ```

6. Copilot がプロジェクトを調べ、データレイヤー、UI、テストに関係するファイルを見つけて変更し、テストを実行する様子を確認します。

   ![Copilot がプロジェクト内のファイルを調べている様子を示すスクリーンショット](../../../_images/ex3-agent-mode-explores.png)

> [!NOTE]
> Copilot はプロジェクトを調べ、ファイルを変更し、テストを実行します。タスクやコードベースの複雑さによって数分かかる場合があります。作業中、エディターに **Keep** と **Undo** が表示される場合があります。作業が終わると、変更ごとに **Keep** または **Undo** が表示されます。処理中に選択する必要はありません。

7. Copilot が求めたら **Continue** を選択してテストを実行します。

   ![Copilot Chat ペインにテスト実行の確認ダイアログが表示されたスクリーンショット](../../../_images/ex3-agent-mode-run-tests.png)

8. 作業中に一時停止したり、テストが失敗したりする場合があります。Copilot はエラーを検出しなくなるまでコード生成とテストを繰り返します。

   ![Copilot Agent Mode での Chat セッションが完了した画面](../../../_images/ex3-agent-mode-proposed-changes.png)

9. 生成されたコードに問題がないか確認します。

> [!CAUTION]
> Copilot などの AI ツールが生成したコードは、必ずレビューしてください。

10. Web サイトを開いているブラウザーに戻り、新しい機能を試します。
11. 動作を確認してコードをレビューしたら、Copilot Chat ウィンドウで **Keep** を選択します。

## まとめと次のステップ

GitHub Copilot Agent Mode を使って Tailspin Toys に機能を追加しました。Agent Mode が UI とデータレイヤーを更新し、プロジェクトを調べて関連ファイルを特定し、複数の変更を行う方法を確認しました。また、コードベースにマージする前に変更とテストをレビューしました。

次は、[Playwright MCP server で機能をテストし][next-lesson]、pull request を作成します。

### 追加演習 - ページネーションを実装する

ゲームの一覧が増えるとページネーションが必要です。この演習で学んだことを使って、Copilot にページネーションの実装を依頼します。

- 指示ファイルを含め、既存のベストプラクティスに従います。
- ページサイズをユーザーが選べるようにするか、固定にするかを検討します。
- 希望する実装に必要なガイダンスをプロンプトで伝えます。
- Copilot に変更やコンテキストを追加で伝えながら反復する場合があります。これは通常の作業です。

## リソース

- [Copilot の ask、edit、agent mode: それぞれの役割と使い分け][choose-mode]
- [VS Code の agent mode][vs-code-agent-mode]

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-mcp/
[choose-mode]: https://github.blog/ai-and-ml/github-copilot/copilot-ask-edit-and-agent-modes-what-they-do-and-when-to-use-them/
[vs-code-agent-mode]: https://code.visualstudio.com/docs/copilot/chat/chat-agent-mode
[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
