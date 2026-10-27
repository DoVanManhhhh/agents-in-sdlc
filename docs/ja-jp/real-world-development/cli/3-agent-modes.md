---
title: "レッスン 3 - エージェントモード: Plan と Autopilot"
description: "Plan でアプローチに合意し、Autopilot で Issue からフィルター機能を構築して、Interactive で結果をレビューします。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

最初は小さな機能を追加しましたが、大きな変更にはより堅牢なプロセスが必要です。GitHub Copilot CLI は組織の既存の開発フローに沿って作業できます。このレッスンでは、Issue から新機能を計画し、コードが有効で期待どおりに動作することを確認し、プロジェクトにマージするまでの一般的なエージェント主導の開発プロセスを始めます。

> [!NOTE]
> 機能のワークフローでは、同じ会話とブランチを使用します。通常はファイルの種類ごとに異なるブランチや PR を使いますが、ここでは中心的な概念に集中できるよう手順を簡略化します。

このレッスンでは、次の内容を学習します。

- GitHub Issue から新しい Copilot の会話を開始する。
- Plan モードで要件を定義する。
- Autopilot モードで機能を実装する。
- コードをレビューする。
- 転送されたブラウザーで機能を手動検証する。

この機能の作業を続けながら、リポジトリの指示を更新し、既存の `quality-checks` スキルをカスタマイズし、MCP による検証を追加して QA エージェントを作成し、機能の PR を開きます。

## シナリオ

Tailspin Toys のカタログが増え、訪問者がカテゴリーとパブリッシャーでゲームを絞り込める機能が必要になりました。バックログの Issue には機能が記載されていますが、カテゴリーの組み合わせ方など、実装前に合意すべき詳細があります。Plan モードで決定し、Autopilot による範囲を限定した実装を承認します。

## 背景

AI コーディングエージェントを開発フローに導入しても基本は変わりません。むしろ、基本はさらに重要になります。多くの開発者は次のような流れで作業します。

1. 必要な作業の説明がある Issue を開く。
2. 構築する内容を計画する。
3. コードを作成してレビューする。
4. テストを実行してコードを検証する。
5. 新機能を手動で検証する。
6. pull request (PR) を作成する。
7. コードレビューと継続的インテグレーションが成功したら、コードをマージする。

> [!NOTE]
> 正確な手順はチームや組織によって異なりますが、多くの場合は上記の流れを調整したものです。

この標準的な手順に従えば、AI が生成したコードが要件を満たし、手作業で作成したコードと同じレビューを受けるようにできます。

## 会話モード

**会話モード**は、エージェントがどれだけ自律的に作業するかを制御します。<kbd>Shift</kbd>+<kbd>Tab</kbd> を押すとモードを切り替えられます。

- **Interactive**: ユーザーとエージェントが共同で作業します。エージェントは変更を提案し、続行前に入力を待ちます。
- **Plan**: エージェントが計画を作成します。エージェントはプロジェクトファイルを編集できません。
- **Autopilot**: エージェントがコードを書き、テストを実行し、完了するまで自律的に反復します。

Plan モードで開始し、計画をレビューしてから Autopilot で実装します。

## Issue から始める

フィルター機能に着手する前に Codespace に戻り、リポジトリとターミナルを準備します。

1. Codespace に戻ります。停止している場合は再起動します。
2. 星評価の PR がマージされていることを確認します。
3. ターミナルが開いていない場合は、<kbd>Control</kbd>+<kbd>\`</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>\`</kbd> (Windows/Linux) を押します。
4. `main` を更新し、フィルター機能用のブランチを作成します。

   ```bash
   git checkout main
   git pull --ff-only
   git checkout -b game-filters-cli
   ```

5. Copilot CLI を起動します。

   ```bash
   copilot --yolo
   ```

6. <kbd>Tab</kbd> を2回押して **Issues** タブを開きます。
7. <kbd>A</kbd> を押してすべての Issue を表示します。
8. 矢印キーで **Allow users to filter games by category and publisher** というタイトルの Issue を選択します。
9. <kbd>C</kbd> を押して Issue をプロンプトに追加し、**Session** タブに戻ります。

プロンプトが `#7` (または同様の番号) で始まることを確認します。`#` を使うと、GitHub 上の Issue や pull request (PR) をコンテキストに追加できます。

## フィルター機能を計画する

計画すると、Copilot に作業を依頼する前にアプローチを決められます。複雑なタスクは事前に計画することをお勧めします。

1. <kbd>Shift</kbd>+<kbd>Tab</kbd> を押して Plan モードに切り替え、プロンプトの下に **Plan** と表示されていることを確認します。
2. Issue の参照に続けて、次のプロンプトを入力します。

   ```plaintext
   Create a plan for implementing this feature.
   ```

Copilot はプロジェクトを調べ、最適な方法を計画します。フィルターの動作について質問されたら、希望する内容を回答してください。唯一の正解はありません。

3. 計画が完成したら、<kbd>Control</kbd>+<kbd>E</kbd> (Mac) または <kbd>Ctrl</kbd>+<kbd>E</kbd> (Windows/Linux) を押して展開します。
4. 計画を読み、決定に合わない箇所の修正を依頼します。

## Autopilot を承認する

計画を確認したら、Autopilot で実装します。Autopilot は、完了したと判断するまで問題に取り組みます。

1. **Accept plan and build on autopilot (recommended)**、またはインストール済みのバージョンで同等のオプションを選択します。
2. プロンプトの下に **Autopilot** と表示されていることを確認します。
3. 計画に沿って Copilot がコードを作成し、テストを実行する様子を確認します。

> [!NOTE]
> 承認すると実装がすぐに始まる場合があるため、先に計画をレビューしてください。依存関係が不足していたりポートが競合したりする場合は、チェック完了と判断する前にセットアップの問題を解決します。

## 実装をレビューして検証する

コードの生成後は、マージ前にレビューします。

1. <kbd>Shift</kbd>+<kbd>Tab</kbd> を押して Interactive モードに切り替え、モード表示が **Plan** や **Autopilot** ではないことを確認します。
2. `/diff` を入力し、フィルター機能の実装とテストを確認します。
3. 結果を Issue と計画時の決定に照らし合わせます。
4. レビュー後、<kbd>Esc</kbd> を押して差分画面を閉じます。
5. プロジェクトのチェック結果を確認し、失敗があれば Copilot に修正を依頼します。

## 新機能を試す

Codespaces で転送されたポートからサイトを開き、実際に動作することを確認します。

1. Copilot にアプリの起動を依頼します。

   ```plaintext
   Start the app so I can try the filtering feature in my browser. Tell me the URL and leave the server running.
   ```

2. Codespaces でポート `4321` が利用可能になったら **Open in Browser** を選択します。
3. カテゴリー、パブリッシャー、計画で合意した組み合わせを試します。
4. リセット時と結果がない場合の動作が、Issue と決定内容に合っていることを確認します。
5. Codespace に戻り、起動した開発サーバーを Copilot に停止させます。

## まとめと次のステップ

異なる会話モードを使って機能を構築し、レビューしました。このレッスンでは、Issue から会話を開始し、Plan モードで要件を定め、Autopilot で機能を実装し、コードをレビューして、転送されたブラウザーで動作を確認しました。

次は、文書化されたプラクティスにコードを従わせるため、[カスタム指示を使用します][next-lesson]。

## リソース

- [GitHub Copilot CLI の Autopilot][autopilot]
- [Copilot CLI コマンド リファレンス][cli-reference]

[autopilot]: https://docs.github.com/copilot/concepts/agents/copilot-cli/autopilot
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[previous-lesson]: ../2-add-star-rating/
[next-lesson]: ../4-custom-instructions/
