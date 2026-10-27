---
title: "レッスン 5 - quality-checks スキルをカスタマイズして使う"
description: "既存の quality-checks スキルを確認し、結果の形式をカスタマイズして、フィルター機能を検証します。"
authors:
  - geektrainer
lastUpdated: 2026-09-29
---

コードを書くこと以外にも、必要な作業があります。これまで手動でコードを確認し、指示ファイルで標準に従わせました。テスト、lint、その他の継続的インテグレーション (CI) の作業はどうでしょうか。

このようなタスクには、**エージェントスキル**が適しています。スキルを使うと、こうした操作を正しく実行する方法を Copilot に伝えられます。

このレッスンでは、次の内容を学習します。

- 既存の `quality-checks` スキルを確認する。
- 結果の形式をカスタマイズする。
- スキルを再読み込みして実行する。

## シナリオ

Tailspin Toys では、単体テスト、lint、型チェックに `quality-checks` スキルを使用しています。チームは、結果を読みやすくするため、報告形式を改善したいと考えています。

## 指示、スクリプト、リソース

エージェントスキルは、再利用可能なタスク指示、実行可能なスクリプト、補助リソースをまとめ、必要なときにエージェントが読み込むものです。基本的には、スキル名のフォルダーと、その中にある `SKILL.md` ファイルで構成されます。Markdown ファイルには、スキルの内容を定義する `name` と `description` の frontmatter、概要、呼び出すタイミングのガイダンスを記述します。フォルダーには、呼び出されたスキルが使用するスクリプトやその他のリソースを含めることもできます。

> [!NOTE]
> スキルに追加のフォルダーやファイルは必須ではありません。Tailspin Toys の `quality-checks` スキルは、プロジェクトにあるコマンドを使うため、`SKILL.md` だけで構成されています。

スキルは、チームで共有・再利用するリポジトリアセットとして `.github/skills` に配置するか、ユーザーのスキルフォルダー `~/.copilot/skills` に配置できます。

## スキルを確認する

Tailspin Toys のチームが単体テスト、lint、型チェックを実行するために作成した `quality-checks` スキルを確認します。

1. Codespace に戻り、Codespaces エディターで `.github/skills/quality-checks/SKILL.md` を開きます。
2. 先頭の `name` と `description` を読みます。`description` によって、Copilot はスキルを呼び出すタイミングを判断します。
3. 指示を読み、テストと lint の手順がどのように説明されているか確認します。
4. まだ **Results output formatting** セクションがないことを確認します。

## 変更前にスキルを実行する

Copilot CLI から直接、または自然言語を使ってスキルを呼び出せます。まず、3つのチェックを実行するよう Copilot に依頼します。

1. Interactive モードでフィルター機能の会話に戻ります。
2. 次のプロンプトを送信します。

   ```plaintext
   Run the quality-checks skill for unit tests, lint, and type checks.
   ```

3. 最後に出力された報告を確認します。

## 結果の報告形式をカスタマイズする

実行した処理、成功・失敗の状態、ツールの報告内容がわかるようにしましょう。`.github/skills/quality-checks/SKILL.md` の末尾に次のセクションを追加します。

```markdown
## Results output formatting

Upon completion, report each command that ran and whether it passed, failed, or was blocked. Include test counts, durations, errors, warnings, and other metrics only when the tool reports them. Identify the next action for any failure or blocker, and never describe a skipped or incomplete check as passed.
```

ファイルは自動的に保存されます。

## 更新したスキルを実行する

変更したスキルは、会話を再開せずに Copilot CLI で再読み込みできます。

1. 次を入力します。

   ```plaintext
   /skills reload
   ```

2. 先ほどと同じプロンプトを送信します。

   ```plaintext
   Run the quality-checks skill for unit tests, lint, and type checks.
   ```

3. 最初の結果と比較し、最後に出力された報告を確認します。

## まとめと次のステップ

既存のエージェントスキルをカスタマイズして使用しました。このレッスンでは、単体テスト、lint、型チェック向けの `quality-checks` スキルを確認し、結果の報告形式をカスタマイズして、スキルを再読み込みして実行しました。

この変更はフィルター機能の PR に含めます。次は、[Playwright MCP server を使ってサイトを操作します][next-lesson]。

## スキルの例

次のコミュニティ例は参考資料であり、追加の課題ではありません。

- [Agent Skills 仕様][skill-spec]
- [コントリビューションのワークフロー: `make-repo-contribution`][contribution-example]
- [要件ドキュメント: `prd`][prd-example]
- [図とエクスポートスクリプト: `drawio`][drawio-example]
- [ブラウザーテスト: `webapp-testing`][browser-example]

[previous-lesson]: ../4-custom-instructions/
[next-lesson]: ../6-mcp-playwright/
[skill-spec]: https://agentskills.io/specification
[contribution-example]: https://github.com/github/awesome-copilot/tree/main/skills/make-repo-contribution
[prd-example]: https://github.com/github/awesome-copilot/tree/main/skills/prd
[drawio-example]: https://github.com/github/awesome-copilot/tree/main/skills/drawio
[browser-example]: https://github.com/github/awesome-copilot/tree/main/skills/webapp-testing
