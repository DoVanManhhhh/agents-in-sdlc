---
title: "レッスン 4 - カスタム指示で Copilot を導く"
description: "リポジトリの指示を確認し、ドキュメント標準を追加して、フィルター機能のコードに適用します。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

生成 AI を使うときは、コンテキストが重要です。タスクを特定の方法で進める必要がある場合、そのガイダンスを Copilot が利用できるようにします。[指示ファイル][instruction-files]には、作成するコードだけでなく、その構成方法も記述できます。フィルター機能を実装したので、Copilot が使った指示を確認し、ドキュメント標準を追加して、コードに適用します。

このレッスンでは、次の内容を学習します。

- リポジトリの指示とパスごとの指示ファイルがエージェントに適用される仕組みを確認する。
- コーディング標準に従うよう指示ファイルを更新する。
- 指示ファイルがコードに与える影響を確認する。

## シナリオ

Tailspin Toys には開発プラクティスに関するガイドラインがあります。

- コメントではコードを言い換えるのではなく、意図や自明でない判断を説明します。
- `db/` と `src/lib/` のエクスポート関数には、目的、パラメーター、戻り値を記載する TSDoc/JSDoc を付けます。該当する場合は注入可能な `db` 引数も記載します。
- 再利用可能な Astro コンポーネントでは `Props` の契約を文書化し、関連コードが変わったときはコメントを更新します。
- 既存の書式設定と lint のガイダンスを維持します。

指示ファイルを使い、Copilot がこれらのプラクティスに沿って作業できるようにします。

## 指示ファイル

カスタム指示は、コーディングスタイルや要件を Copilot に伝えるコンテキストです。リポジトリ全体に適用する指示も、特定のファイルに適用する指示も作成できます。

指示ファイルには次の2種類があります。

- `.github/copilot-instructions.md`: リポジトリのすべてのリクエストで Copilot に送信される、プロジェクト全体向けの指示ファイルです。
- `.github/instructions/*.instructions.md`: 特定の言語、ファイル種別、タスクに関するガイダンスを定義します。

> [!NOTE]
> 指示ファイルの対応形式は環境によって異なります。特定の形式を前提にする前に、[カスタム指示のサポート状況][custom-instructions-support]を確認してください。

## このプロジェクトのカスタム指示ファイルを確認する

変更を加える前に、スタータープロジェクトに含まれる指示ファイルを確認します。

1. Codespace に戻ります。
2. Codespaces エディターで `.github/copilot-instructions.md` を開きます。
3. プロジェクトの概要とコーディングガイダンスを確認します。この指示は、このリポジトリに関するすべての Copilot とのやり取りに適用されます。
4. `.github/instructions` フォルダーを開き、Astro、Drizzle データレイヤー、テストなどの指示を確認します。
5. `.github/instructions/unit-tests.instructions.md` を開き、先頭の `applyTo` フィールドが適用対象の glob を定義していることを確認します。
6. `.github/instructions/drizzle.instructions.md` を開き、他の指示ファイルや既存のプロジェクトファイルへのリンクを確認します。指示を再利用可能な複数のファイルに分け、Copilot に例を示せます。

## チームのガイダンスに合わせて指示ファイルを更新する

既存の指示は出発点として十分ですが、TypeScript に新しい TSDoc コメントを追加する標準が不足しています。`.github/copilot-instructions.md` の **Code formatting guidance** セクションの最後に、次の項目を追加します。

```markdown
- All new TypeScript should contain TSDocs comments for documentation purposes.
```

ファイルは自動的に保存されます。

## 更新したガイダンスを適用する

Copilot CLI は会話の開始時にリポジトリの指示を読み込みます。更新した指示を適用するため、会話を終了してフィルター機能の会話を再開します。

1. フィルター機能の会話が開いている場合は `/exit` を入力します。会話は自動的に保存されます。
2. リポジトリのルートで `game-filters-cli` ブランチをチェックアウトし、保存済みの会話を再開します。

   ```bash
   copilot --resume
   ```

3. 求められた場合はフィルター機能の会話を選択し、`game-filters-cli` ブランチがチェックアウトされていることを確認します。
4. Copilot に次のように依頼します。

   ```plaintext
   We just updated our instructions and code guidance. Can you please update the code you generated to match that guidance?
   ```

5. `/diff` を入力し、変更された TypeScript ファイルを確認します。新しい TSDoc コメントが追加され、コードを正確に説明していることを確認します。

## まとめと次のステップ

Copilot CLI が指示ファイルからコンテキストを取得する仕組みを確認し、新しい標準を追加して機能のコードに適用しました。次は、[再利用可能な quality-checks スキルをカスタマイズして実行し][next-lesson]、lint とテストを一貫して実施します。

## リソース

- [Copilot CLI のカスタム指示を追加する][instruction-files]
- [カスタム指示のサポート状況][custom-instructions-support]
- [効果的なカスタム指示を作成するためのベストプラクティス][instructions-best-practices]
- [Awesome Copilot — 指示ファイルなどのコレクション][awesome-copilot]

[instruction-files]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot/add-custom-instructions
[instructions-best-practices]: https://docs.github.com/copilot/concepts/prompting/response-customization#writing-effective-custom-instructions
[awesome-copilot]: https://awesome-copilot.github.com/
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support
[previous-lesson]: ../3-agent-modes/
[next-lesson]: ../5-agent-skills/
