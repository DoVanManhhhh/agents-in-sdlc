---
title: "レッスン 0 - 前提条件"
description: "Tailspin Toys の自分用コピーを作成し、Copilot CLI ワークショップ用の GitHub Codespace を準備します。"
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

Copilot CLI のレッスンを始める前に、必要な準備を整えます。Tailspin Toys リポジトリの自分用コピーを作成して [Codespace][codespaces] を立ち上げます。次のレッスンでは、Codespace の統合ターミナルを使って Copilot CLI をインストールし、実行します。

このレッスンでは、次の内容を学習します。

- テンプレートから Tailspin Toys プロジェクトの自分用コピーを作成する。
- Codespace を作成し、プロジェクトを使える状態にする。

## ラボ用リポジトリを設定する

これから作成するコードのために、[テンプレートリポジトリ][tailspin-template]から自分用のコピーを作成します。新しいリポジトリにはラボに必要なすべてのファイルが含まれています。

1. 新しいブラウザーウィンドウで [Tailspin Toys テンプレート][tailspin-template]を開きます。
2. ラボ用リポジトリのページで **Use this template** を選択し、**Create a new repository** を選択してコピーを作成します。
3. GitHub または Microsoft が主催するイベントの一環として参加している場合は、メンターの指示に従います。それ以外の場合は、GitHub Copilot を利用できる Organization に新しいリポジトリを作成します。
4. 後で参照するため、作成したリポジトリのパス (`organization-or-user-name/repository-name`) を控えておきます。

> [!NOTE]
> テンプレートからリポジトリを作成すると、GitHub Issue のバックログが自動的に作成されます。ワークショップ全体で使うため、自分で Issue を作成する必要はありません。

ワークショップのテンプレートの新しいコピーを使用してください。リポジトリの指示、アプリケーションコード、テスト、`quality-checks` スキル、使用するバックログが含まれています。古いコピーを使用する場合は、必要なファイルがあることを進行役に確認してください。

## Codespace を作成する

次は、Codespace を使ってワークショップを進めます。

[GitHub Codespaces][codespaces] は、ブラウザーからコードを作成、実行、デバッグできるクラウド開発環境です。複数のプログラミング言語、拡張機能、ツールに対応した高機能なエディターを利用できます。

1. 作成したリポジトリを開きます。
2. **Code** を選択します。
3. **Codespaces** タブを選び、**Create codespace on main** を選択します。
4. Codespace のセットアップが完了するまで待ちます。テンプレートによってプロジェクトの依存関係、Playwright Chromium、ローカルデータベースがインストールされます。
5. **Do you trust the authors of the files in this folder?** と表示されたら、**Trust Folder & Continue** を選択します。
6. リポジトリのルートでターミナルを開き、アプリケーションを起動します。

   ```bash
   npm run dev
   ```

7. Codespaces でポート `4321` が利用可能になったら **Open in Browser** を選択し、Tailspin Toys のサイトが読み込まれることを確認します。
8. ターミナルに戻り、<kbd>Ctrl</kbd>+<kbd>C</kbd> を押して開発サーバーを停止します。

## まとめと次のステップ

準備ができました。このレッスンでは、テンプレートから Tailspin Toys の自分用コピーを作成し、Codespace を準備して、プロジェクトが使えることを確認しました。

次は、Codespace に [GitHub Copilot CLI をインストールし][next-lesson]、GitHub アカウントで認証します。

## リソース

- [GitHub Codespaces の概要][codespaces]
- [テンプレートからリポジトリを作成する][template-repository]
- [Codespaces クイックスタート][codespaces-quickstart]

[tailspin-template]: https://github.com/github-samples/tailspin-toys
[template-repository]: https://docs.github.com/repositories/creating-and-managing-repositories/creating-a-template-repository
[codespaces-quickstart]: https://docs.github.com/codespaces/getting-started/quickstart
[next-lesson]: ../1-install-copilot-cli/
[codespaces]: https://github.com/features/codespaces
