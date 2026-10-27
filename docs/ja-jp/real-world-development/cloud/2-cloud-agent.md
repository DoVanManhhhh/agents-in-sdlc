---
title: "演習 2 - GitHub Copilot cloud agent"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← 前のレッスン: カスタム指示][previous-lesson] |
|:--|

多くの組織では、技術的負債が課題になっています。未解決のセキュリティ問題、更新が必要なレガシーコード、実装する時間がなくバックログに残った機能要望などがあります。GitHub Copilot の cloud agent は、コードの更新や機能の追加などを自律的に実行できます。作業が終わると、人間の開発者がレビューできるドラフトの pull request を作成します。手間のかかる作業を任せて開発を速め、開発者はより大きな課題に集中できます。

Copilot cloud agent を使って次の内容を確認します。

- コード生成環境のカスタマイズ。
- 操作を安全に行う方法。
- Issue の範囲を明確にする重要性。
- Issue を Copilot に割り当てる方法。

## シナリオ

Tailspin Toys には解消したい技術的負債があります。最初の Web サイトを作成した開発チームは、ドキュメントを十分に作成していません。まず、アプリケーションのエクスポート関数すべてに TSDoc のドキュメントコメントを追加します。

また、デザインチームはゲームを見つけやすくしたいと考えています。各ゲームの詳細ページに、同じカテゴリーの他のタイトルを「関連ゲーム」として表示し、UX の受け入れテストに使える状態にします。洗練された完成形はまだ必要ありません。現在はブロッカーですが、さらに優先度の高い Issue があります。

どちらも優先順位が下がりやすいタスクです。Copilot cloud agent に割り当てれば、非同期に作業を進められます。その間、別の作業に集中し、後から結果をレビューできます。

## GitHub Copilot cloud agent とは

[GitHub Copilot cloud agent](https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent#overview-of-copilot-cloud-agent-formerly-copilot-coding-agent) は、人間の開発者と同様にバックグラウンドでタスクを実行できます。[GitHub Issue を Copilot に割り当てる][assign-issue]方法などがあります。割り当て後、Copilot は進行状況を追跡するドラフト pull request を作成し、環境を準備してタスクに取り組みます。進行中でも完了後でもセッションを確認できます。提案された解決策のレビュー準備ができると、pull request で通知されます。

## 適切な範囲の指示が重要

GitHub Copilot に魔法はありません。考える作業を省略できるわけではありません。一見簡単な操作でも、詳しく見ると複雑な場合があります。[Copilot cloud agent に依頼するタスクの範囲を慎重に決めてください][cloud-agent-best-practices]。AI ペアプログラマーとして扱い、段階的に作業し、学び、試し、必要に応じて調整します。生成 AI を導入しても、ソフトウェア開発の基本は変わりません。

## このリポジトリのカスタム指示

これまでの演習ではカスタム指示と、Copilot をガイドする方法を確認しました。まだ `.github/copilot-instructions.md` を見ていない場合は、ここで読み取り専用で確認してください。後で cloud agent の作業にどのように影響するかを見ます。

リポジトリの GitHub Web UI または起動中の Codespace で次のファイルを開きます。

- `.github/copilot-instructions.md`: **Code standards** セクションの TypeScript 規約と TSDoc コメントに関する要件を確認します。
- `.github/instructions/unit-tests.instructions.md`: `applyTo` frontmatter が、これらの指示を `**/*.test.ts` ファイルに適用していることを確認します。

次のセクションで `Code lacks documentation` Issue を cloud agent に割り当てます。生成される PR に TSDoc コメント、TypeScript 規約、ファイルヘッダーが反映されているか確認してください。後の演習で PR をレビューするときに、もう一度取り上げます。

## Copilot cloud agent の開発環境を設定する

コードの作成では、開発環境やセットアップスクリプトを実行する必要があることがよくあります。Copilot にタスクを割り当てる場合も同様です。

cloud agent は作業環境に [GitHub Actions][github-actions] を使います。`.github/workflows/copilot-setup-steps.yml` に設定する[専用のセットアップワークフロー][setup-workflow]を作成すると、作業前に開発ツールや依存関係をインストールできます。ラボでは、流れを簡単にし、この仕組みを学べるよう事前に設定されています。単一の Astro アプリで使う Node.js、プロジェクトの依存関係、E2E テスト用ブラウザー、マイグレーションと seed 済みの SQLite データベースを用意します。

```yaml
name: "Copilot Setup Steps"

# リポジトリの Actions タブからセットアップ手順をテストできます。
on: workflow_dispatch

env:
  ASTRO_TELEMETRY_DISABLED: "1"

jobs:
  copilot-setup-steps:
    runs-on: ubuntu-latest
    # Copilot は操作用の独自トークンを受け取るため、セットアップに必要な最小限の権限を設定します。
    permissions:
      # セットアップでリポジトリをクローンする場合 (依存関係のインストールなど) は `contents: read` が必要です。クローンしない場合、セットアップ後に Copilot が自動的にクローンします。
      contents: read
    steps:
      - name: Checkout code
        uses: actions/checkout@v5

      # フロントエンドとアプリのセットアップ。アプリ全体は Astro と Drizzle/libSQL で構成されています。
      - name: Set up Node.js
        uses: actions/setup-node@v6
        with:
          node-version: "lts/*"
          cache: "npm"
          cache-dependency-path: "./package-lock.json"

      - name: Install JavaScript dependencies
        run: npm ci

      - name: Install Playwright browsers
        run: npx playwright install --with-deps chromium

      # ビルドとテスト用にローカル SQLite データベースをマイグレーションし、seed します。
      - name: Set up the database
        run: npm run db:setup
```

他の GitHub workflow と似ていますが、主なポイントは次のとおりです。

- `copilot-setup-steps` という1つのジョブがあり、Copilot が pull request の作業を始める前に GitHub Actions で実行されます。
- `workflow_dispatch` トリガーにより、リポジトリの **Actions** タブから手動で実行できます。Copilot が実行するのを待たずに、ワークフローをテストできます。

## ドキュメントを追加する

多くのプロジェクトでは、ドキュメントが古いか不足しています。こうした技術的負債は放置されやすく、開発の効率を下げ、コードベースの保守や新しい開発者の参加を難しくします。Copilot はドキュメント作成が得意なので、この Issue を cloud agent に割り当てます。Copilot はバックグラウンドで必要なドキュメントを作成し、後の演習で結果を確認します。

1. 新しいブラウザータブで github.com のリポジトリを開きます。
2. **Issues** タブを選択します。
3. **New issue** を選択して新しい Issue の画面を開きます。
4. **Blank issue** を選択します。
5. **Title** に `Code lacks documentation` と入力します。
6. **Description** に次の内容を入力します。

   ```plaintext
   Our organization has a requirement that functions and methods include TSDoc doc comments where helpful. Unfortunately, recent updates haven't followed this standard. We need to update the existing code to ensure doc comments are included where they clarify behavior.
   ```

7. **Create** を選択して Issue を作成します。
8. 右側にある **Assign to Copilot** を選択して割り当て画面を開きます。

   ![Issue に Copilot を割り当てる画面](../../../_images/shared-assign-copilot.png)

9. **Assign** を選択します。
10. **Pull Requests** タブを選択します。
11. 新しく作成された pull request (PR) を開きます。タイトルは `[WIP]: Code lacks documentation` などになります。まだ一覧に表示されていない場合は、少し待ってブラウザーを更新します。
12. 数分後、Copilot が作成した TODO リストを確認します。

> [!NOTE]
> PR に TODO リストが表示されるまで数分かかる場合があります。Copilot は環境を準備し (先ほどのワークフローを実行し)、プロジェクトを分析して、作業の進め方を決めています。

13. TODO リストと、実行予定のタスクを確認します。
14. pull request のタイムラインを下にスクロールし、Copilot が Issue の作業を開始したことを確認します。
15. **View session** を選択します。

   ![Copilot のセッションビュー](../../../_images/ex4-view-session.png)

> [!CAUTION]
> 更新された表示を確認するため、ブラウザーを更新する必要がある場合があります。

16. セッションをスクロールし、Copilot が問題を解決する様子を確認します。コードを調査して状態を把握し、計画を考え、コードを作成する手順が表示されます。

作業には数分かかる場合があります。cloud agent の主な目的は、作業を非同期で実行し、その間に別のタスクを進められるようにすることです。別の Issue も Copilot cloud agent に割り当て、その間にアプリケーションの機能を実装します。

## ゲーム詳細ページに関連ゲームを追加する

GitHub Copilot cloud agent の利点の1つは作業を分けられることです。デザインチーム向けに関連ゲームを表示する作業は時間がかからないかもしれませんが、その時間を別の作業に使えるよう cloud agent に割り当てます。

1. github.com のリポジトリに戻ります。
2. **Issues** タブを選択します。
3. **New issue** を選択します。
4. **Blank issue** を選択します。
5. **Title** に `Show related games on the game details page` と入力します。
6. **Description** に次の内容を入力します。

   ```markdown
   We want to help people discover more games by showing related games on each game's details page. The design team wants to explore the UX and do some acceptance testing. Our requirements are:

   - Add a data-access helper in `src/lib/` that returns other games in the same category as a given game, excluding that game
   - Show a "Related games" section on the game details page that uses the helper
   - Handle the case where a game has no related games
   - There should be unit tests created for the new helper
   - Before creating the PR, ensure all tests pass
   ```

7. **Create** を選択して Issue を作成します。
8. 右側にある **Assign to Copilot** を選択して割り当て画面を開きます。

   ![Issue に Copilot を割り当てる画面](../../../_images/shared-assign-copilot.png)

9. **Assign** を選択します。

最初の Issue のコメントに 👀 が表示されると、Copilot が作業を開始したことがわかります。

![Copilot が Issue の作業中であることを目の絵文字で示している画面](../../../_images/ex4-issue-eyes-emoji.png)

Copilot は2つ目の依頼に取り組んでいます。cloud agent はソフトウェアエンジニアのように作業するため、常に監視する必要はありません。完了後にレビューします。次は、カスタムエージェントの作成と使用を確認します。

## まとめと次のステップ

[GitHub Copilot cloud agent][copilot-agents] に Issue を割り当て、技術的負債への対応、新機能の作成、フレームワーク間のコード移行などを非同期で実行できることを確認しました。また、コード生成環境のカスタマイズ、安全な操作、Issue の範囲設定について学びました。

cloud agent がバックグラウンドで作業している間に、[カスタムエージェントを作成して使います][next-lesson]。[Copilot cloud agent は MCP server も使用できます][cloud-agent-mcp]。前のモジュールで確認したカスタム指示も利用できます。

## リソース

- [Copilot cloud agent について][copilot-agents]
- [GitHub Issue を Copilot に割り当てる][assign-issue]
- [Copilot cloud agent のセットアップワークフローのベストプラクティス][cloud-agent-best-practices]

| [次のレッスン: カスタムエージェント →][next-lesson] |
|--:|

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-custom-agents/
[cloud-agent-mcp]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/extend-cloud-agent-with-mcp
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[github-actions]: https://docs.github.com/actions
