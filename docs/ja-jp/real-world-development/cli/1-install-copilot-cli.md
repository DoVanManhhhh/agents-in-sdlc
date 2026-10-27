---
title: "レッスン 1 - GitHub Copilot CLI をインストールする"
description: "Codespace に Copilot CLI をインストールして認証し、使い方を確認して、用意されたフィルター機能の Issue を見つけます。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

[GitHub Copilot CLI][about-copilot-cli] は、ターミナルで動作するエージェント型コーディングアシスタントです。コードベースを探索し、コードを生成し、コマンドを実行し、外部ツールを利用できます。タスクを任せたり、変更を依頼したりしながら、コマンドラインで作業を続けられます。まずは、使い慣れたツールで Copilot CLI をインストールします。

このレッスンでは、次の内容を学習します。

- npm で GitHub Copilot CLI をインストールする。
- GitHub アカウントで認証する。
- ワークショップのリポジトリを信頼し、簡単な会話を試す。
- 組み込みの GitHub MCP server でフィルター機能の Issue を見つける。

## シナリオ

チームでは、増え続けるバックログに対応するため AI エージェントを使い始めています。Copilot CLI は、多くの開発者が日常的に使うターミナルでエージェントを利用できるようにします。このレッスンでは、残りのワークショップで使えるようにインストールと認証を行います。

## Copilot CLI をインストールする

Copilot CLI は [npm][install-cli]、WinGet、Homebrew からインストールできます。GitHub Codespaces には Node.js があらかじめインストールされているため、ここでは npm を使います。

1. Codespace に戻り、ターミナルを開きます。
2. Node.js がインストールされ、必要なバージョンを満たしていることを確認します。

   ```bash
   node --version
   ```

   バージョン 24 以上が表示されます。

3. Copilot CLI をグローバルにインストールします。

   ```bash
   npm install -g @github/copilot
   ```

4. インストールを確認します。

   ```bash
   copilot --version
   ```

   バージョン番号が表示されます。

## GitHub で認証する

Copilot CLI を初めて起動すると、GitHub アカウントでの認証を求められます。

1. Copilot CLI を起動します。

   ```bash
   copilot
   ```

2. 認証を求められた場合は、device code の手順に従って認証し、Copilot CLI を承認します。
3. Copilot CLI に次のプロンプトが表示されます。

   ```plaintext
   Copilot can read files in this folder and, with your permission, edit them or run code and shell commands. It will remember your permissions for the rest of this session.

   Do you trust the files in this folder?
   ```

4. パスが Tailspin Toys リポジトリであることを確認し、**Yes, and remember this folder for future sessions** を選択します。

> [!NOTE]
> Codespace では GitHub セッションを通じてすでに認証されている場合があります。認証のプロンプトが表示されずに Copilot CLI が起動すれば、そのまま続行できます。

## 基本操作を確認する

通常のシェルプロンプトでは Codespace 上でコマンドを実行します。Copilot CLI の起動後は、自然言語でエージェントに指示し、スラッシュコマンドで会話を操作します。

1. `/model` を入力し、矢印キーで **Auto** を選択して <kbd>Enter</kbd> を押し、もう一度 <kbd>Enter</kbd> を押して確定します。
2. `/help` を入力してインストール済みバージョンで利用できるコマンドを確認し、<kbd>Esc</kbd> を押してヘルプを閉じます。
3. Copilot に簡単な質問をして動作を確認します。

   ```plaintext
   What are the key files in this project?
   ```

4. 回答を読み、Copilot が回答前にリポジトリを調べることを確認します。
5. `/mcp list` を実行し、組み込みの GitHub MCP server が利用できることを確認します。
6. Copilot にフィルター機能の Issue を探させます。

   ```plaintext
   Using GitHub MCP, find the issue in this repository titled "Allow users to filter games by category and publisher." Give me its URL and a short summary. Don't change anything.
   ```

7. URL を開き、Issue を読みます。最初の小さな変更を終えた後、この Issue から作業を始めます。

> [!TIP]
> 通常の Copilot CLI セッションは、ターミナルでチェックアウトされているブランチを使用し、自動的に worktree を作成しません。変更を始める前に機能ブランチを作成します。

## ワークショップ用のショートカットを使う

通常、Copilot CLI は、許可されていないツールを使う前に確認を求めます。このワークショップでは `--yolo` を付けて再起動し、Codespace 内でその確認を省略して演習に集中します。

> [!CAUTION]
> `--yolo` は、`--allow-all-tools`、`--allow-all-paths`、`--allow-all-urls` による完全な自動権限を有効にします。Codespace や VM などの分離された環境でのみ使い、日常の開発で既定値として alias に設定しないでください。詳しくは[ツールの使用を許可または禁止する方法][allow-all-warning]を参照してください。

`--enable-all-github-mcp-tools` は、後のレッスンで Issue や pull request を操作する際に使う、読み取りと書き込みの GitHub MCP ツールを有効にします。Codespace によってローカルコンピューターへのアクセスは制限されますが、認証済みの GitHub リソースにはアクセスできます。公開やマージの前に変更をレビューしてください。

1. `/exit` で Copilot CLI を終了します。
2. リポジトリのルートから再起動します。

   ```bash
   copilot --yolo --enable-all-github-mcp-tools
   ```

3. プロジェクトについて簡単な質問をして会話が動作することを確認し、`/exit` で終了します。

Copilot は会話を自動的に保存します。後で指示を変更したりエージェントを追加したりした後、`copilot --resume` で同じ機能の会話とブランチを再開します。

## まとめと次のステップ

GitHub Copilot CLI を npm でインストールし、GitHub アカウントで認証して、ワークショップのリポジトリを信頼し、組み込みの GitHub MCP server からフィルター機能の Issue を見つけました。

次は、[最初の変更に着手し][next-lesson]、Copilot CLI でゲームカードに星評価を表示します。

## リソース

- [GitHub Copilot CLI をインストールする][install-cli]
- [GitHub Copilot CLI について][about-copilot-cli]
- [Copilot CLI コマンド リファレンス][cli-reference]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-add-star-rating/
[install-cli]: https://docs.github.com/copilot/how-tos/copilot-cli/set-up-copilot-cli/install-copilot-cli
[about-copilot-cli]: https://docs.github.com/copilot/concepts/agents/about-copilot-cli
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[allow-all-warning]: https://docs.github.com/copilot/concepts/agents/about-copilot-cli#allowing-and-denying-tool-use
