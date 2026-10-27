---
title: "演習 1 - カスタム指示 (Cloud agent)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← 前のレッスン: 前提条件][previous-lesson] · [次のレッスン: Copilot cloud agent →][next-lesson]

生成 AI を使うときは、コンテキストが重要です。タスクを特定の方法で進める必要がある場合や、Copilot に背景情報を伝えたい場合は、そのコンテキストを利用できるようにします。[指示ファイル][instruction-files]を使うと、何をするかだけでなく、どのように実行するかも Copilot に伝えられます。

この演習では、次の内容を学習します。

- リポジトリのカスタム指示とパスごとの指示ファイルを使い、プロジェクト固有のコンテキスト、コーディングガイドライン、ドキュメント標準を Copilot に伝える方法。
- `.github/copilot-instructions.md` にリポジトリ全体の標準を追加する方法。

> [!NOTE]
> VS Code や CLI の演習とは異なり、ここでは更新前と更新後のプロンプトを比較しません。Copilot cloud agent は GitHub Issue 上で非同期に作業するため、リアルタイムで並べて効果を示すのが難しいためです。この演習の後半で、cloud agent が生成した pull request をレビューし、指示ファイルの影響を確認します。

## 指示ファイル

### シナリオ

Tailspin Toys には開発プラクティスに関するガイドラインがあります。

- データレイヤーには必ず単体テストを用意します。
- UI はダークモードにし、現代的な見た目にします。
- TSDoc のドキュメントコメントをコードに追加します。
- 各ファイルの先頭に、ファイルの役割を説明するコメントブロックを追加します。

指示ファイルを使い、Copilot がこれらのプラクティスに沿ってタスクを進められるようにします。

### カスタム指示

カスタム指示は、コーディングスタイルや要件を Copilot に伝えるコンテキストです。希望するコーディング規約、ライブラリ、コードコメントの種類を指定し、Copilot が適切な提案やコードを作成できるようにします。リポジトリ全体または特定のファイル種別やタスクに指示を適用できます。

指示ファイルには次の2種類があります。

- `.github/copilot-instructions.md` は、リポジトリに関する**すべての**リクエストで Copilot に送信される単一の指示ファイルです。技術スタック、構築するものの概要、ベストプラクティスなど、プロジェクト全体に関係する情報を記載します。
- `.github/instructions/*.instructions.md` は、特定のタスクやファイル種別に作成できる指示ファイルです。TypeScript や Astro などの言語、UI コンポーネントの作成や単体テストの作成などのタスクに関するガイダンスを記載します。

> [!NOTE]
> IDE では、指示ファイルは Copilot Chat のコード生成にのみ使われ、コード補完や次の編集候補には適用されません。
>
> Copilot Chat、Copilot CLI、Copilot cloud agent は、リポジトリレベルの指示と `applyTo` frontmatter を持つ `*.instructions.md` ファイルを使用します。
>
> Copilot は AGENTS.md や CLAUDE.md など、別の規格の指示ファイルにも対応しています。[カスタム指示のサポート状況][custom-instructions-support]を確認してください。

### 指示ファイルを管理するためのベストプラクティス

指示ファイルの作成に関する詳しい説明はこのワークショップの範囲外ですが、サンプルプロジェクトには代表的な方法が含まれています。

- `copilot-instructions.md` は、構築するもの、プロジェクト構成、全体のコーディング標準など、プロジェクト全体のガイダンスに絞ります。
- `*.instructions.md` は、単体テスト、Astro コンポーネント、データレイヤーなどのファイル種別やタスクに固有の指示に使います。
- 自然な言葉で明確に書き、コード例を使って望ましい形と避けるべき形を示します。

指示ファイルの作成方法は1つではありません。実際に試し、プロジェクトに合う方法を見つけてください。

> [!TIP]
> GitHub Copilot を使うプロジェクトには、十分な指示ファイルがあると役立ちます。このプロジェクトには、[UI 更新][ui-instructions]や [Astro][astro-instructions] などの指示があります。
>
> Copilot に指示ファイルを生成させることもできます。VS Code では **Configure Chat → Generate Agent Instructions**、Copilot CLI では `/init` など、環境によって方法が異なります。利用している環境向けのレッスンで説明します。
>
> テンプレートやひな型を探す場合は、指示ファイルやカスタムエージェントなどを集めた [awesome-copilot][awesome-copilot] を確認してください。

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## このプロジェクトのカスタム指示ファイルを確認する

リポジトリにある指示ファイルを読みます。中心となる `copilot-instructions.md` と、タスク別の `*.instructions.md` が含まれています。GitHub Web UI または起動中の Codespace で開いてください。

1. `.github/copilot-instructions.md` を開きます。
2. プロジェクトの概要と、**Agent notes**、**Code standards**、**Scripts**、**Repository Structure** などのセクションを確認します。**Code standards** の下には、ネストされた **GitHub Actions Workflows** のガイダンスもあります。これらの指示は Copilot とのあらゆるやり取りに適用されます。
3. `.github/instructions` フォルダーを開き、Astro ファイル、Drizzle データレイヤー、テストなどの指示を確認します。
4. `.github/instructions/unit-tests.instructions.md` を開きます。先頭の `applyTo` フィールドがリポジトリのルートを基準とする glob を定義しています。例として、`**/*.test.ts` に一致する TypeScript のテストファイルが対象です。
5. このプロジェクトで単体テストを作成するための指示を確認します。
6. `.github/instructions/drizzle.instructions.md` を開き、末尾にある他の指示ファイル (`unit-tests.instructions.md` など) やプロジェクト内の既存ファイルへのリンクを確認します。大きな指示セットを小さく再利用可能なファイルに分け、Copilot に例を示せます。ここに記載されたパスは、リポジトリのルートではなく指示ファイルの場所を基準としています。

> [!NOTE]
> `copilot-instructions.md` の **Code formatting requirements** セクションにはプロジェクトの標準が記載されていますが、コード内のドキュメント化はまだ必須ではありません。次の手順で TSDoc コメントとファイル先頭のコメントを追加します。

## リポジトリの新しい標準を追加する

この演習で行う編集は、プロジェクト全体に適用する標準を追加することです。コード内の TSDoc コメントとファイル先頭のコメントブロックをルールに含めます。cloud agent は、この演習の後半で割り当てる Issue に取り組むときに、更新した指示を読み取ります。

編集する前に作業用のブランチを作成します。cloud agent は Issue が対象とするブランチから指示を読みますが、変更を整理してコミットします。

1. Codespace のターミナルで新しいブランチを作成し、切り替えます。

   ```bash
   git checkout -b custom-instructions-cloud
   ```

`.github/copilot-instructions.md` にプロジェクト全体のガイダンスを記載します。

1. `.github/copilot-instructions.md` を開き直します。
2. **Code formatting requirements** セクションを見つけます。プロジェクトの標準は記載されていますが、コードのドキュメント化に関するルールがありません。
3. 既存の標準の直後に、次の Markdown を追加し、ファイル先頭のコメントと TSDoc コメントを Copilot に指示します。

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. `copilot-instructions.md` を保存します。

> [!TIP]
> 指示ファイルは、リポジトリレベル (`.github/copilot-instructions.md`) に置いて全体に適用することも、特定の言語、ファイル種別、タスク向けの `*.instructions.md` として作成することもできます。今回追加するドキュメントコメントのルールはプロジェクト全体の標準なので、リポジトリレベルのファイルに適しています。

## 指示の更新をコミット、プッシュ、マージする

cloud agent は、Issue が対象とするブランチから指示ファイルを読み込みます。次の演習で Copilot に Issue を割り当てると、cloud agent は `main` からブランチを作成するため、更新した指示が `main` に入っている必要があります。

1. 変更をステージしてコミットします。

   ```bash
   git add .github/copilot-instructions.md
   git commit -m "Add doc comment and file-header standards to copilot instructions"
   ```

2. ブランチをプッシュします。

   ```bash
   git push -u origin custom-instructions-cloud
   ```

3. github.com で `custom-instructions-cloud` から `main` に向けた pull request を開き、マージします。次の演習で Issue を割り当てるとき、cloud agent は更新した指示を読み込みます。

> [!TIP]
> このワークショップでは `main` に直接作業してもかまいません。その場合はブランチの作成を省略して、`main` に直接コミットします。ブランチを使う手順は、実際のプロジェクトと同じ流れにするためのものです。

## まとめと次のステップ

Copilot が指示ファイルからコンテキストを取得する仕組みを確認し、`.github/copilot-instructions.md` に新しい標準を追加しました。残りの演習で cloud agent が作成する pull request に、その標準がどのように反映されるかを確認します。

次は、[最初の Issue を Copilot cloud agent に割り当てます][next-lesson]。

## リソース

- [GitHub Copilot のカスタマイズに使う指示ファイル][instruction-files]
- [カスタム指示を作成するためのベストプラクティス][instructions-best-practices]
- [Copilot のカスタム指示を改善するための5つのヒント][copilot-instructions-five-tips]
- [Awesome Copilot - 指示ファイルなどのコレクション][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-cloud-agent/
[instruction-files]: https://docs.github.com/copilot/customizing-copilot/about-customizing-github-copilot-chat-responses
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
