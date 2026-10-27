---
title: "演習 1 - カスタム指示 (VS Code)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 前のレッスン: 前提条件][previous-lesson] · [次のレッスン: Agent mode →][next-lesson]

生成 AI を使うときは、コンテキストが重要です。タスクを特定の方法で進める必要がある場合や、Copilot に背景情報を伝えたい場合は、そのコンテキストを利用できるようにします。Copilot に具体的なコンテキストを共有する方法はいくつかあります。その中心となるのが[指示ファイル][instruction-files]です。指示ファイルでは、コード生成に関するガイダンスを伝えられます。

この演習では、次の内容を学習します。

- リポジトリのカスタム指示とパスごとの指示ファイルを使い、プロジェクト固有のコンテキスト、コーディングガイドライン、ドキュメント標準を Copilot に伝える。
- 現在の指示に従ってフィルター機能の最初のデータ部分 (publishers ヘルパー) を作成する。
- `.github/copilot-instructions.md` にリポジトリ全体の標準を追加する。
- 同じプロンプトを再実行し、生成コードが新しい標準に従うことを確認する。
- 指示の更新とフィルター機能の一部を `main` にコミットし、次の演習で新しい指示を利用できるようにする。

> [!CAUTION]
> 生成コードが設定した標準から外れる場合があります。Copilot の動作は確率的です。この演習では、文字単位で同じ出力を得るのではなく、指示の更新後に動作がどのように変化するかを確認します。

## 指示ファイル

### シナリオ

Tailspin Toys には開発プラクティスに関するガイドラインがあります。

- データレイヤーには必ず単体テストを用意します。
- UI はダークモードにし、現代的な見た目にします。
- TSDoc のドキュメントコメントをコードに追加します。
- 各ファイルの先頭に、ファイルの役割を説明するコメントブロックを追加します。

指示ファイルを使い、Copilot がこれらのプラクティスに沿ってタスクを実行できるようにします。

### カスタム指示

カスタム指示は、コーディングスタイルや要件を Copilot に伝えるためのコンテキストです。コーディング規約、ライブラリ、コメントの書き方などを指定でき、リポジトリ全体または特定のタスクやファイルの種類に適用できます。

指示ファイルには次の2種類があります。

- `.github/copilot-instructions.md` は、リポジトリに関するすべてのリクエストで Copilot に送信される単一の指示ファイルです。多くのリクエストに関係するプロジェクト全体のコンテキストを記載します。
- `.github/instructions/*.instructions.md` は、特定のタスクやファイルの種類に適用するガイドラインを定義します。

> [!NOTE]
> IDE では、指示ファイルは Copilot Chat のコード生成にのみ使われ、コード補完や次の編集候補には適用されません。
>
> Copilot Chat、Copilot CLI、Copilot cloud agent は、リポジトリレベルの指示と、`applyTo` frontmatter を持つ `*.instructions.md` ファイルを使用します。
>
> Copilot は AGENTS.md や CLAUDE.md など、別の規格の指示ファイルにも対応しています。[カスタム指示のサポート状況][custom-instructions-support]を確認してください。

### 指示ファイルを管理するためのベストプラクティス

完全な指示ファイルを作成する方法はこのワークショップの範囲外ですが、サンプルプロジェクトには代表的な方法が含まれています。

- `copilot-instructions.md` は、構築するもの、プロジェクト構成、全体のコーディング標準など、プロジェクト全体のガイダンスに絞ります。
- `*.instructions.md` には、単体テスト、Astro コンポーネント、データレイヤーなどのファイル種別やタスクに固有の指示を記載します。
- 自然な言葉で、明確なガイダンスとコード例を示します。

指示ファイルの作成方法は1つではありません。実際に試し、プロジェクトに合う方法を見つけてください。

> [!TIP]
> GitHub Copilot を使うプロジェクトには、十分な指示ファイルがあると役立ちます。このプロジェクトには、[UI 更新][ui-instructions]や [Astro][astro-instructions] など、さまざまなタスク向けのファイルが含まれています。
>
> Copilot に指示ファイルを作成させることもできます。VS Code の **Configure Chat → Generate Agent Instructions**、Copilot CLI の `/init` など、環境によって方法が異なります。利用している環境向けのレッスンで説明します。
>
> テンプレートやひな型を探す場合は、指示ファイル、カスタムエージェントなどを集めた [awesome-copilot][awesome-copilot] を確認してください。

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## このプロジェクトのカスタム指示ファイルを確認する

このリポジトリにある指示ファイルを読みます。中心となる `copilot-instructions.md` と、タスク別の `*.instructions.md` が含まれています。エディターまたは GitHub Web UI で開いてください。

1. `.github/copilot-instructions.md` を開きます。
2. プロジェクトの概要と、**Agent notes**、**Code standards**、**Scripts**、**Repository Structure** などのセクションを確認します。これらの指示は Copilot とのあらゆるやり取りに適用されます。
3. `.github/instructions` フォルダーを開き、Astro ファイル、Drizzle データレイヤー、テストなどの指示を確認します。
4. `.github/instructions/unit-tests.instructions.md` を開きます。先頭の `applyTo` フィールドがリポジトリルートを基準とする glob を定義しています。たとえば `**/*.test.ts` に一致する TypeScript のテストファイルに適用されます。
5. このプロジェクトで単体テストを作成するための指示を確認します。
6. `.github/instructions/drizzle.instructions.md` を開き、末尾にある他の指示ファイル (例: `unit-tests.instructions.md`) やプロジェクト内の既存ファイルへのリンクを確認します。指示を小さく再利用可能なファイルに分け、コード生成の例を示せます。ここにあるパスはリポジトリルートではなく、指示ファイルの場所を基準にしています。

> [!NOTE]
> `copilot-instructions.md` の **Code formatting requirements** セクションにはプロジェクトの標準が記載されていますが、コード内のドキュメントコメントはまだ必須ではありません。後の手順で TSDoc コメントとファイル先頭のコメントを追加します。

## 変更用のブランチを作成する

ベストプラクティスに従って、変更用のブランチを作成します。

1. 前の演習で使った Codespace に戻ります。
2. <kbd>Control</kbd>+<kbd>`</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux) を押して、新しいターミナルを開きます。
3. 新しいブランチを作成して切り替えます。

   ```bash
   git checkout -b custom-instructions
   ```

## 指示を更新する前に Copilot Chat を使う

> [!TIP]
> **Copilot Chat を開く**
>
> 次の手順に進む前に Codespace に戻り、Copilot Chat パネルを開いて **New Chat** を選択し、新しい会話を始めます。モードとモデルの選択は演習によって異なるため、必要な設定を各手順で説明します。

カスタム指示の効果を確認するため、まず現在の指示ファイルの状態でプロンプトを送信します。後で指示を更新して、同じプロンプトをもう一度送信します。

1. 前の演習で使ったエディタータブを閉じ、Copilot が必要なコンテキストだけを取得するようにします。
2. `src/lib/publishers.ts` を開き、ヘルパーの作成場所を Copilot に示します。
3. Chat ビューのエージェントドロップダウンから **Agent** を選択し、Copilot がファイルを変更できるようにします。

   ![Chat ビューのエージェントピッカーを示すスクリーンショット。](../../../_images/shared-chat-mode-selector.png)

4. 次のプロンプトを送信します。

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

5. Copilot はプロジェクトを確認してコードを更新します。ヘルパーファイルとテストの両方が変更されることがあります。
6. 提案されたヘルパーが、`db` クライアントを最初の引数に取り、型付きのパブリッシャー配列を返す関数であることを確認します。これは `src/lib/*.ts` に適用される `.github/instructions/drizzle.instructions.md` の規約によるものです。
7. 生成コードに TSDoc コメントとファイル先頭のコメントがないことを確認します。

> [!CAUTION]
> Copilot は確率的に動作するため、指示がなくてもドキュメントコメントを追加することがあります。その場合も問題ありません。ここでは、指示の更新後に一貫性が改善されることを確認します。

## リポジトリの標準を追加する

`.github/copilot-instructions.md` は Copilot にプロジェクト全体の情報を伝えるファイルです。コード生成のガイダンスを改善するため、新しい標準を追加します。

1. `.github/copilot-instructions.md` を開き直します。
2. **Code formatting requirements** セクションを見つけます。プロジェクトの標準は記載されていますが、コードのドキュメント化に関するルールがありません。
3. 既存の標準の直後に、次の Markdown を追加し、ファイル先頭のコメントと TSDoc コメントを Copilot に指示します。

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. `copilot-instructions.md` を保存します。

> [!TIP]
> 指示ファイルは、リポジトリレベル (`.github/copilot-instructions.md`) に置いて全体に適用することも、言語やファイルの種類、タスクに固有の `*.instructions.md` として作成することもできます。今回追加するコードコメントのルールは、プロジェクト全体の標準なので、リポジトリレベルのファイルに適しています。

## プロンプトを再実行して変化を確認する

1. Copilot Chat に戻り、**New Chat** を選択してコンテキストをクリアします。
2. `src/lib/publishers.ts` を選択し、Copilot が対象ファイルを把握できるようにします。
3. 先ほどと**同じプロンプト**を送信します。

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

4. 提案されたファイルの先頭に、次のようなコメントブロックがあることを確認します。

   ```typescript
   /**
    * Tailspin Toys のクラウドファンディングプラットフォーム向けパブリッシャーデータアクセスヘルパー。
    * データベースからパブリッシャー情報を取得する関数を提供します。
    */
   ```

5. 提案された関数に、次のような TSDoc コメントがあることを確認します。

   ```typescript
   /**
    * ID と名前を含むすべてのパブリッシャーの一覧を返します。
    *
    * @param db - Drizzle データベースクライアント。
    * @returns パブリッシャーオブジェクトの配列で解決される Promise。
    */
   ```

Copilot に新しいプロジェクト標準を守らせ、それを次の演習で利用する実際のコードに適用できました。

## 指示とブランチをコミットしてプッシュする

指示ファイルも他のリポジトリアセットと同じようにソース管理します。変更をコミットしてブランチをリポジトリにプッシュします。

1. <kbd>Control</kbd>+<kbd>`</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux) を押して、新しいターミナルを開きます。
2. 次のコマンドを実行し、指示とヘルパーの変更を確認します。

   ```bash
   git status
   ```

3. 指示の更新とヘルパーの基礎となる変更をステージしてコミットします。

   ```bash
   git add .github/copilot-instructions.md src/lib/publishers.ts
   # git status にテストなどの追加変更が表示された場合は、それらのファイルも追加します。
   git commit -m "Add doc comment standards and publishers helper foundation"
   ```

4. ブランチをリポジトリにプッシュします。

   ```bash
   git push -u origin custom-instructions
   ```

## pull request を作成してマージする

プッシュしたブランチから pull request を作成し、バックログのドキュメント標準に関する Issue に関連付けます。GitHub のツールを使って、Copilot に Issue の検索、PR の作成、マージを依頼できます。

> [!NOTE]
> Copilot が GitHub 上で操作するのは、この演習が初めてです。プロジェクトのテンプレートには GitHub のツールがあらかじめ設定されているため、追加設定は必要ありません。Copilot が初めてツールを使うときは、VS Code で GitHub へのサインインを求められることがあります。画面の指示に従ってください。後の演習では、この接続に使われる Model Context Protocol について学びます。

1. Codespace で Copilot Chat を開きます。
2. <kbd>Control</kbd>+<kbd>Command</kbd>+<kbd>I</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>I</kbd> (Windows/Linux) を押して Copilot Chat ビューを開き、エージェントピッカーで **Agent** が選択されていることを確認します。
3. 指示ファイル更新の Issue を検索し、現在のブランチから PR を作成するよう Copilot に依頼します。

   ```plaintext
   Find the issue related to updating the instructions file. Create a new PR from the current branch, highlight that the PR closes that issue, and include that we also added the publishers helper foundation for the upcoming filtering work.
   ```

4. Copilot が Issue を検索して PR を作成します。
5. GitHub の操作を許可するよう求められた場合は、コマンドを確認して必要に応じて **Allow** を選択します。
6. PR が作成されたら、次のプロンプトでマージしてローカルのブランチを `main` に戻すよう依頼します。

   ```plaintext
   Merge the PR into main. Then return to main locally, and pull the latest code so we are up to date.
   ```

7. GitHub の操作やシェルコマンドを許可するよう求められた場合は、内容を確認して必要に応じて **Allow** を選択します。

GitHub Copilot の支援で pull request を作成し、マージできました。

## まとめと次のステップ

Copilot がこのプロジェクトの指示を参照する仕組みを確認し、VS Code の Copilot Chat を使って、既存の指示でコード生成の結果を確認しました。次に `.github/copilot-instructions.md` にリポジトリ全体の標準を追加し、同じプロンプトを再実行して結果への影響を確認しました。最後に、指示の更新とヘルパーの基礎をコミットして `main` にマージし、次の演習で使えるようにしました。

次は、[agent mode][next-lesson]で指示を活用し、Copilot にコードベース全体にまたがる機能を追加させます。

## リソース

- [GitHub Copilot のカスタマイズに使う指示ファイル][instruction-files]
- [カスタム指示を作成するためのベストプラクティス][instructions-best-practices]
- [Copilot のカスタム指示を改善するための5つのヒント][copilot-instructions-five-tips]
- [GitHub Copilot の個人用カスタム指示][personal-instructions]
- [Awesome Copilot — 指示ファイルなどのコレクション][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-agent-mode/
[instruction-files]: https://code.visualstudio.com/docs/copilot/copilot-customization
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[personal-instructions]: https://docs.github.com/copilot/customizing-copilot/adding-personal-custom-instructions-for-github-copilot
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
