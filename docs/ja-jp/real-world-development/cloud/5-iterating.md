---
title: "演習 5: GitHub Copilot の作業を反復して改善する"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← 前のレッスン: エージェントの管理][previous-lesson] |
|:--|

## 作業をレビューする

このラボでは、ユーザー体験を改善して機能を追加する複数のタスクを GitHub Copilot に依頼しました。コードへのドキュメント追加、デザインチームが試せる関連ゲーム機能の作成、ハイコントラストとライトモードを含むアクセシビリティ機能の実装を依頼しました。コードの変更を確認し、必要に応じて Copilot にフィードバックを送って改善しましょう。

### シナリオ

生成 AI を利用しても、ソフトウェア設計や DevOps の基本は変わりません。生成されたコードをレビューし、通常の DevOps プロセスに沿って作業します。チームにレビューを依頼する前に、ドキュメント、関連ゲーム機能、アクセシビリティ機能について GitHub Copilot が提案した内容を確認します。

## GitHub Copilot cloud agent のセキュリティ

Copilot cloud agent は非同期に、監督を受けずに作業するため、安全性を保つための制約があります。

- Copilot はリポジトリへの読み取りアクセスを持ち、書き込みはコード用ブランチに対してのみ許可されます。
- cloud agent は GitHub Actions 内で、作業用の独立した一時環境を作成します。
- GitHub Actions workflow の実行には、人間による承認が必要です。
- 既定では [外部リソースへのアクセスが制限されており](https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-firewall)、MCP server も対象です。

## 生成されたドキュメントをレビューする

最初に、GitHub Copilot cloud agent がコードにドキュメントを追加する PR を確認します。github.com の標準的な PR 画面を使用します。

> [!NOTE]
> PR に、GitHub Copilot がファイアウォールでブロックされたという警告が表示される場合があります。これは想定された動作です。Copilot は、外部 MCP server への接続を含む外部リソースへのアクセスが既定で制限されています。必要に応じて、[Copilot cloud agent のファイアウォールをカスタマイズまたは無効化][agent-firewall]できます。

1. github.com のリポジトリに戻ります。
2. **Pull Requests** を選択して PR の一覧を開きます。
3. **Add missing documentation** などのタイトルの pull request を開きます。

> [!NOTE]
> Copilot がまだ作業中の場合、pull request に **[WIP]** が付きます。作業が完了するまで待ってください。数分かかることがあります。その間に休憩したり、これまでに学んだことを振り返ったりできます。

4. pull request の準備ができたら **Files changed** タブを選び、変更をレビューします。

   ![Files changed タブ](../../../_images/shared-pr-files-changed.png)

5. TSDoc のドキュメントコメントなど、新しく追加されたドキュメントを確認します。変更内容は状況によって異なります。演習 2 で確認した指示ファイルによる TSDoc コメント、TypeScript 規約、ファイルヘッダーに注目してください。
6. 内容を確認し、問題がなければ **Conversation** タブに戻って下にスクロールします。
7. workflow の実行承認を待っていることを示す表示を確認します。
8. 承認待ちの workflow があれば **Approve and run workflows** を選択します。

   ![Approve and run workflows](../../../_images/shared-approve-workflows.png)

9. pull request の checks セクションに workflow が登録されます。問題がなければ、単一の Astro アプリのプロジェクトチェックが成功します。完了まで数分かかることがあります。

## GitHub Copilot に変更を依頼する

pull request で Copilot とやり取りすることもできます。チームのメンバーと同じように、PR やコード行内のコメントで **@copilot** をメンションすると、Copilot がコメントを確認して変更に対応する新しいセッションを開始します。結果は確率的に変わるため、決まった指示文はありません。次のような変更を依頼できます。

- 各コードファイルの先頭に、役割を簡潔に説明するコメントを追加する。
- TypeScript と Astro のファイルに TSDoc のドキュメントコメントを追加する。
- Astro アプリの構成を説明する README を作成する。

1. **@copilot** をメンションして、ドキュメントの変更を依頼するコメントを追加します。上記の例から選ぶか、コードベースに必要なドキュメントを依頼します。
2. **View Session** を選択し、Copilot の作業を確認します。更新のために新しいセッションが始まります。
3. **Back to pull request** を選択すると PR に戻れます。

   ![Back to pull request](../../../_images/ex7-back-to-pr.png)

4. Copilot の作業が完了すると、pull request に新しいコミットが追加されます。
5. **Files changed** タブで変更をレビューします。

問題がなければ、必要に応じて反復を続けます。満足したら、ドラフト PR をレビュー可能な状態に変更して `main` ブランチにマージします。

![PR をレビュー可能な状態にする操作](../../../_images/ex7-ready-for-review.png)

## 関連ゲーム機能をレビューする

次は、ゲーム詳細ページに関連ゲームを表示する Issue を解決するため、Copilot が作成した PR を確認します。

1. GitHub.com のリポジトリに戻ります。
2. **Pull Requests** タブを選択します。
3. **Show related games on the game details page** などのタイトルの PR を選択します。
4. **Files changed** タブを選択し、生成されたコードを確認します。
5. 内容を確認し、問題がなければ **Conversation** タブに戻って下にスクロールします。
6. workflow の実行承認を待っていることを示す表示を確認します。
7. 承認待ちの workflow があれば **Approve and run workflows** を選択します。

   ![Approve and run workflows](../../../_images/shared-approve-workflows.png)

8. pull request の checks セクションに workflow が登録されます。問題がなければ、単一の Astro アプリのプロジェクトチェックが成功します。完了まで数分かかることがあります。
9. **任意:** Codespace でこのブランチに切り替えて、関連ゲーム機能を手動でテストできます。Codespace のターミナルを開き、Copilot が作成したブランチ名 (例: **copilot/fix-8**) に置き換えて次のコマンドを実行します。

   ```bash
   git fetch origin
   git checkout <branch-name>
   ```

関連ゲーム機能ができました。ほかの PR と同様に、Copilot cloud agent に追加の更新を依頼できます。たとえば表示する関連ゲームの数を調整したり、コメントヘッダーや TSDoc コメントを追加したりできます。この Issue はカスタム指示を更新する前に割り当てたため、その点も確認しましょう。**Conversation** タブにコメントを追加すれば、Copilot が確認して新しいセッションを開始します。

## アクセシビリティ機能をレビューする

最後に、アクセシビリティカスタムエージェントが実装した機能を確認します。この PR には、演習 3 で依頼したハイコントラストモードと、演習 4 の Mission control で追加依頼したライトモードの両方が含まれているはずです。

1. GitHub.com のリポジトリに戻ります。
2. **Pull Requests** タブを選択します。
3. **Add high contrast mode to website** などのタイトルの PR を選択します。

> [!NOTE]
> Copilot がまだ作業中の場合、pull request に **[WIP]** が付きます。作業が完了するまで待ってください。数分かかることがあります。

4. **Files changed** タブを選択し、生成されたコードをレビューします。
5. 実装を確認します。特に次の点を確認してください。
   - モードを切り替える UI コンポーネント。
   - ユーザー設定を保持する local storage の使用。
   - ハイコントラストとライトモードの CSS またはスタイルの変更。
   - アクセシビリティ属性 (ARIA ラベル、キーボード操作など)。
   - モードの切り替えを管理する JavaScript/TypeScript コード。
6. 内容を確認し、問題がなければ **Conversation** タブに戻って下にスクロールします。
7. workflow の実行承認を待っていることを示す表示を確認します。
8. 承認待ちの workflow があれば **Approve and run workflows** を選択します。

   ![Approve and run workflows](../../../_images/shared-approve-workflows.png)

9. pull request の checks セクションに workflow が登録されます。問題がなければ、単一の Astro アプリのプロジェクトチェックが成功します。完了まで数分かかることがあります。
10. **任意:** Codespace でブランチに切り替えてアクセシビリティ機能を手動テストできます。Codespace のターミナルを開き、Copilot が作成したブランチ名に置き換えて次のコマンドを実行します。

   ```bash
   git fetch origin
   git checkout <branch-name>
   ```

アプリケーションを起動し、ブラウザーでハイコントラストとライトモードを切り替えます。ページを再読み込みしても設定が保持されることを確認してください。

アクセシビリティカスタムエージェントが、ベストプラクティスに従って機能を実装するよう Copilot を導いたことを確認します。アクセシビリティ上の懸念や改善点があれば、前の PR と同じようにコメントで **@copilot** をメンションして更新を依頼できます。

## 任意の演習 - 作業の委任を続ける

cloud agent は、バックログの実際の Issue を任せ、その間に別の作業に取り組むと効果的です。習慣として身に付けるため、リポジトリに Issue を追加して Copilot に割り当ててみましょう。

- ゲーム詳細ページに支援者向けの関心フォームを作成する。
- ゲーム一覧にページネーションを実装する。
- データアクセスヘルパーに入力検証とエラー処理を追加する。

## まとめ

Cloud agent の演習を完了しました。このレッスンでは、次の内容を学びました。

- **このリポジトリに含まれるカスタム指示ファイルを確認し**、cloud agent の結果への影響を確認する準備をした。
- **Copilot cloud agent に Issue を割り当て**、環境を準備し、計画を立て、非同期に作業する様子を確認した。
- **カスタムエージェントを作成して使い**、ハイコントラストとライトモードの切り替えを追加した。
- **Copilot agents ページを Mission control として使い**、アクセシビリティセッションを監視して指示した。
- **cloud agent の pull request をレビューして反復し**、`@copilot` に変更を依頼して workflow を承認した。

## 振り返りと次のステップ

Cloud agent の演習を完了しました。さらに学ぶ場合は、ほかの演習で今回の内容を発展できます。

- 🖥️ **[VS Code の演習](../../vscode/)** — IDE から Copilot Chat の agent mode と MCP 統合を確認します。
- 💻 **[CLI の演習](../../cli/)** — Plan と Autopilot、エージェントスキル、QA カスタムエージェント、Playwright MCP、Agent Merge、任意の `/delegate` を使い、ターミナルから2つの変更をレビューして公開します。

自分のリポジトリでも次の内容を試してください。

- リファクタリングやテストカバレッジの Issue を cloud agent に割り当てる。
- 別の分野向けにカスタムエージェントを作成する。
- 別の技術スタック向けに `copilot-setup-steps.yml` を設定する。

## リソース

- [GitHub Copilot][github-copilot]
- [Copilot agents について][copilot-agents]
- [GitHub Issue を Copilot に割り当てる][assign-issue]
- [Copilot cloud agent のセットアップワークフローのベストプラクティス][cloud-agent-best-practices]
- [Copilot cloud agent のファイアウォールを設定する][agent-firewall]

---

| [← 前のレッスン: エージェントの管理][previous-lesson] |
|:--|

[github-copilot]: https://github.com/features/copilot
[cloud-agent-overview]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[agent-firewall]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-firewall
[previous-lesson]: ../4-managing-agents/
