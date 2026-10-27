---
title: "レッスン 10 - 振り返りと次のステップ"
description: "Copilot CLI のワークフロー、2つの pull request、再利用可能なカスタマイズ、追加リソースを振り返ります。"
authors:
  - geektrainer
lastUpdated: 2026-09-29
---

Tailspin Toys の一連のワークフローで GitHub Copilot CLI を使用しました。このワークショップでは、Codespace を準備し、Copilot CLI をインストールしてプロジェクトを確認し、用意されたフィルター機能の Issue を見つけました。星評価を追加して転送されたブラウザーで確認し、最初の pull request (PR) を手動でマージしました。次に、フィルター機能の計画、Autopilot での実装、Interactive モードでのレビューを行いました。カスタム指示を追加し、`quality-checks` スキルを更新して単体テスト、lint、型チェックを実行し、Playwright Model Context Protocol (MCP) server でブラウザーから機能を確認しました。さらに、要件、カバレッジ、スキルの結果、ブラウザーでの検証証拠を評価する品質保証 (QA) カスタムエージェントを作成して選択しました。最後にフィルター機能全体をレビューし、Agent Merge を許可して PR をマージし、コンテキスト、モデル、共有、任意のクラウド委任に使うスラッシュコマンドを確認しました。

## リリースした内容

このワークショップには、更新済みの `main` から作成した別々のブランチで進める、2つの PR の節目があります。

1. **星評価**: 既存の `starRating` と未評価の場合の表示をゲームカードに追加します。
2. **フィルター機能と品質ワークフロー**: フィルター機能を実装し、指示を更新して機能に適用し、`quality-checks` の報告形式をカスタマイズし、QA プロファイルを作成して、関連するテストを含めます。

フィルター機能の計画から PR の作成まで、同じ会話とブランチを使用しました。ワークショップを簡潔にするため、これらの作業を1つの PR にまとめました。

## さまざまな検証方法

自動テスト、自分で行うブラウザー確認、MCP を通じた Copilot のブラウザー操作という複数の方法でコードを確認しました。`quality-checks` スキルは単体テスト、lint、型チェックを実行し、新しい形式で報告しました。QA はその結果と、要件およびテストカバレッジのレビューをまとめて PR の確認を支援しました。

追加するテストでは、実際に不足している部分を補います。QA の実行で追加テストが不要と判断されることもあります。マージを許可する前にコードと根拠を確認し、変更後は関連する検証結果を更新してください。

## ベストプラクティス

Copilot に与えるコンテキストとツールが、作業結果を左右します。このワークショップでは、指示を更新し、スキルをカスタマイズし、QA プロファイルを作成し、MCP server を設定しました。これらのカスタマイズは会話をまたいで再利用でき、チームのニーズに合わせて調整できます。指示は標準を設定し、スキルは繰り返し実行するタスクを説明し、カスタムエージェントは専門的な役割を定義し、MCP server は外部ツールに接続します。エージェントの要約だけでなく、実際の変更とツールの結果を確認してください。

タスクに合わせて **モードとモデル** を選びます。作業前にアプローチを検討するときは **Plan**、範囲を絞って対話的に進めるときは **Interactive**、範囲が明確なタスクを任せるときは **Autopilot** を使います。定型的な編集には高速なモデルを、複雑な作業にはより高性能なモデルを選びます。

ツールやインフラストラクチャと同じくらい、コンテキストも重要です。何を、なぜ、どのように作るのかを明確に伝えると、結果が大きく変わります。

## さらに試す

主要なワークフローは完了しました。ほかにも、次の CLI 機能を試せます。

- `/review` でコードレビューエージェントに変更を分析してもらいます。
- `/rubber-duck` で問題を整理し、別の視点を得ます。
- `/fleet` で独立したサブタスクを並列に進めます。
- `/worktree` で別のタスクを分離します。
- `/delegate` で Copilot cloud agent にタスクを送ります。

## 次のステップ

どのツールも、使い続けることが上達への近道です。実際のコード、個人のプロジェクト、作ろうと思いながら何年も手を付けられなかった小さなアプリなどで活用してください。チームで学んだことを共有し、互いの経験から学びましょう。ドキュメントも引き続き確認してください。

ターミナルから Tailspin Toys を拡張する場合は、任意の [Foundry Backer Concierge シリーズ][foundry]に進みます。ほかの環境と比較するには、[VS Code ワークショップ][vscode]、[GitHub Copilot app ワークショップ][app]、または [Copilot cloud agent ワークショップ][cloud]を確認してください。

## リソース

- [GitHub Copilot CLI について][about-cli]
- [Copilot CLI コマンド リファレンス][cli-reference]
- [Copilot CLI をカスタマイズする][customize-cli]
- [Copilot CLI で pull request を管理する][manage-prs]

[previous-lesson]: ../9-cli-power-tools/
[foundry]: ../8-foundry-agent/
[vscode]: ../../vscode/
[app]: ../../app/
[cloud]: ../../cloud/
[about-cli]: https://docs.github.com/copilot/concepts/agents/about-copilot-cli
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[customize-cli]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot
[manage-prs]: https://docs.github.com/copilot/how-tos/copilot-cli/use-copilot-cli/manage-pull-requests
