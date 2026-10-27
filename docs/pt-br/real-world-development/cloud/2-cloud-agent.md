---
title: "Exercício 2 - Agente de nuvem do GitHub Copilot"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← Lição anterior: Instruções personalizadas][previous-lesson] |
|:--|

É provável que poucas organizações, se houver alguma, não enfrentem problemas com dívida técnica. Pode ser uma questão de segurança não resolvida, código legado que precisa de atualização ou uma solicitação de recurso que ficou no backlog por falta de tempo para implementá-la. O agente de nuvem do GitHub Copilot foi criado para tarefas como atualizar código e adicionar funcionalidades de forma autônoma. Quando termina, ele gera um rascunho de pull request (PR) para revisão de uma pessoa desenvolvedora. Assim, é possível delegar tarefas repetitivas, acelerar o desenvolvimento e se concentrar em questões mais abrangentes.

Neste exercício, você vai explorar como usar o agente de nuvem do Copilot para:

- personalizar o ambiente de geração de código.
- garantir que as operações sejam realizadas com segurança.
- entender a importância de issues com escopo claro.
- atribuir issues ao Copilot.

## Cenários

A Tailspin Toys tem algumas dívidas técnicas para resolver. As pessoas contratadas inicialmente para criar a primeira versão do site deixaram a documentação em um estado inadequado — na verdade, ela está totalmente ausente. Como primeiro passo, a equipe quer adicionar comentários TSDoc a todas as funções exportadas do aplicativo.

Além disso, a equipe de design quer melhorar a descoberta de jogos. Ela quer que a página de detalhes de cada jogo mostre jogos relacionados — outros títulos da mesma categoria — para que as pessoas possam continuar navegando. A equipe ainda não precisa de uma implementação refinada; quer algo que possa usar para testes de aceitação da experiência. Isso é um bloqueio no momento, mas há outras issues de prioridade mais alta.

Esses são exemplos de tarefas que podem ser facilmente adiadas e que são ótimas candidatas para atribuição ao agente de nuvem do Copilot. O agente trabalha nelas de forma assíncrona enquanto você se dedica a outras tarefas. Depois, você pode revisar o trabalho e confirmar que está tudo certo.

## Conheça o agente de nuvem do GitHub Copilot

O [agente de nuvem do GitHub Copilot](https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent#overview-of-copilot-cloud-agent-formerly-copilot-coding-agent) executa tarefas em segundo plano, de maneira semelhante a uma pessoa desenvolvedora. Assim como no trabalho com uma pessoa desenvolvedora, há várias maneiras de atribuir tarefas, inclusive [atribuindo uma issue do GitHub ao Copilot](https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions). Depois da atribuição, o Copilot cria um pull request de rascunho para acompanhar o andamento, configura um ambiente e começa a trabalhar. Você pode examinar a sessão enquanto o trabalho está em andamento ou depois que ela termina. Quando a solução estiver pronta para revisão, o Copilot mencionará você no pull request.

## A importância de instruções com escopo claro

Não há mágica no GitHub Copilot: não é possível pular a etapa de pensar. Até operações aparentemente simples podem ficar complexas quando examinadas de perto. Por isso, [defina com cuidado o escopo das tarefas para o agente de nuvem do Copilot][cloud-agent-best-practices]. Trate-o como um parceiro de programação com IA: trabalhe em etapas, aprenda, experimente e adapte o processo. Os fundamentos do desenvolvimento de software não mudam com a inclusão da IA generativa.

## Instruções personalizadas neste repositório

Nos exercícios anteriores, você conheceu as instruções personalizadas e como elas orientam o Copilot. Se já concluiu o exercício prático sobre instruções personalizadas, viu `.github/copilot-instructions.md` em ação. Caso contrário, este é um bom momento para examiná-lo. Antes de atribuir trabalho ao agente de nuvem do Copilot, leia os arquivos de instruções existentes neste repositório sem alterá-los para observar o efeito deles depois.

Abra os arquivos a seguir na interface Web do GitHub ou em um Codespace já iniciado:

- `.github/copilot-instructions.md`: examine a seção **Code standards**, principalmente as expectativas sobre convenções TypeScript e comentários TSDoc.
- `.github/instructions/unit-tests.instructions.md`: observe o frontmatter `applyTo`, que limita essas instruções aos arquivos `**/*.test.ts`.

Ao atribuir a issue `Code lacks documentation` ao agente de nuvem na próxima seção, procure comentários TSDoc, convenções TypeScript e cabeçalhos de comentários no pull request resultante. Essas orientações vêm dos arquivos de instruções que você verá novamente ao revisar os PRs em um exercício posterior.

## Configure o ambiente de desenvolvimento do agente de nuvem do Copilot

Desenvolver código normalmente exige um ambiente específico e a execução de scripts de configuração para garantir que tudo esteja pronto. O mesmo vale ao atribuir tarefas ao Copilot, que executa o trabalho de maneira semelhante a uma pessoa engenheira de software.

O agente de nuvem usa o [GitHub Actions][github-actions] como ambiente de trabalho. Você pode personalizá-lo com um [workflow de configuração especial][setup-workflow], definido em `.github/workflows/copilot-setup-steps.yml`, que é executado antes de o agente começar. Assim, ele tem acesso às ferramentas e dependências necessárias. O workflow já está configurado neste laboratório para que você possa acompanhar os exercícios. Ele fornece Node.js, dependências do projeto, binários de navegador para testes de ponta a ponta e o banco de dados SQLite migrado e preenchido para o aplicativo Astro:

```yaml
name: "Copilot Setup Steps"

# Permite testar as etapas de configuração na guia "Actions" do repositório
on: workflow_dispatch

env:
  ASTRO_TELEMETRY_DISABLED: "1"

jobs:
  copilot-setup-steps:
    runs-on: ubuntu-latest
    # Defina as permissões no menor nível necessário para *suas etapas*. O Copilot receberá um token próprio para as operações dele.
    permissions:
      # Para clonar o repositório durante as etapas de configuração, por exemplo, para instalar dependências, você precisará da permissão `contents: read`. Se não clonar o repositório nas etapas, o Copilot fará isso automaticamente depois que elas forem concluídas.
      contents: read
    steps:
      - name: Checkout code
        uses: actions/checkout@v5

      # Configuração do front-end/aplicativo - Node.js (todo o aplicativo agora usa Astro + Drizzle/libSQL)
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

      # Migra e preenche o banco de dados SQLite local para que compilações e testes tenham dados.
      - name: Set up the database
        run: npm run db:setup
```

O arquivo se parece com qualquer outro workflow do GitHub, mas tem alguns pontos importantes:

- Ele contém um único job, `copilot-setup-steps`, executado no GitHub Actions antes de o Copilot começar a trabalhar no pull request.
- O gatilho `workflow_dispatch` permite executar o workflow manualmente na guia **Actions** do repositório. Isso é útil para testar se ele funciona, sem esperar o Copilot executá-lo.

## Adicione documentação

Embora todo mundo reconheça a importância da documentação, muitos projetos têm informações desatualizadas ou não têm documentação. Esse tipo de dívida técnica costuma não ser resolvido, reduzindo a produtividade e dificultando a manutenção da base de código e a integração de novas pessoas desenvolvedoras. Felizmente, o Copilot pode ajudar a criar documentação, e esta é uma issue ideal para atribuir ao agente de nuvem. Ele trabalhará em segundo plano e, em um exercício futuro, você voltará para revisar o resultado.

1. Em uma nova guia do navegador, acesse o repositório no github.com.
2. Selecione a guia **Issues**.
3. Selecione **New issue** para abrir a caixa de diálogo de nova issue.
4. Selecione **Blank issue** para criar uma issue em branco.
5. Defina o **Title** como `Code lacks documentation`.
6. Defina a **Description** como:

    ```plaintext
    Our organization has a requirement that functions and methods include TSDoc doc comments where helpful. Unfortunately, recent updates haven't followed this standard. We need to update the existing code to ensure doc comments are included where they clarify behavior.
    ```

7. Selecione **Create** para criar a issue.
8. No lado direito, selecione **Assign to Copilot** para abrir a caixa de diálogo de atribuição.

  ![Atribuição de uma issue ao Copilot](../../../_images/shared-assign-copilot.png)

9. Selecione **Assign**.
10. Selecione a guia **Pull Requests**.
11. Abra o pull request (PR) recém-gerado, com um título semelhante a `[WIP]: Code lacks documentation`. Se não aparecer um novo PR, aguarde um ou dois minutos e atualize a janela do navegador.
12. Depois de alguns minutos, o Copilot deverá criar uma lista de tarefas.

> [!NOTE]
> A lista de tarefas do Copilot pode levar alguns minutos para aparecer no PR. O Copilot está configurando o ambiente, executando o workflow descrito anteriormente, analisando o projeto e definindo a melhor abordagem para a tarefa.

13. Revise a lista e as tarefas que o Copilot pretende executar.
14. Role a linha do tempo do pull request para baixo. Você verá uma atualização informando que o Copilot começou a trabalhar na issue.
15. Selecione o botão **View session**.

  ![Visualização da sessão do Copilot](../../../_images/ex4-view-session.png)

> [!CAUTION]
> Talvez seja necessário atualizar a janela para ver o indicador atualizado.

16. Observe a sessão em andamento e como o Copilot resolve o problema. Ele explora o código e entende o estado atual, faz pausas para pensar e definir o plano adequado e cria código.

Isso pode levar alguns minutos. Um dos principais objetivos do agente de nuvem do Copilot é executar tarefas de forma assíncrona para que você possa se dedicar a outras atividades. Vamos aproveitar esse recurso: enquanto o agente trabalha, atribuiremos outra tarefa a ele e criaremos código para adicionar funcionalidades ao aplicativo.

## Adicione uma seção de jogos relacionados à página de detalhes

Uma das grandes vantagens do agente de nuvem do GitHub Copilot é poder dividir o trabalho: você se concentra em um conjunto de tarefas enquanto ele trabalha em outro. Mesmo que a seção de jogos relacionados para a equipe de design não leve muito tempo, você poderia usar esse tempo em outras atividades. Vamos atribuir a tarefa ao agente de nuvem do Copilot.

1. Volte ao repositório no github.com.
2. Selecione a guia **Issues**.
3. Selecione **New issue** para abrir a caixa de diálogo de nova issue.
4. Selecione **Blank issue** para usar o template em branco.
5. Defina o **Title** como `Show related games on the game details page`.
6. Defina a **Description** como:

    ```markdown
    We want to help people discover more games by showing related games on each game's details page. The design team wants to explore the UX and do some acceptance testing. Our requirements are:

   - Add a data-access helper in `src/lib/` that returns other games in the same category as a given game, excluding that game
   - Show a "Related games" section on the game details page that uses the helper
   - Handle the case where a game has no related games
   - There should be unit tests created for the new helper
   - Before creating the PR, ensure all tests pass
   ```

7. Selecione **Create** para criar a issue.
8. No lado direito, selecione **Assign to Copilot** para abrir a caixa de diálogo de atribuição.

  ![Atribuição de uma issue ao Copilot](../../../_images/shared-assign-copilot.png)

9. Selecione **Assign**.

Pouco depois, você deverá ver o emoji 👀 no primeiro comentário da issue, indicando que o Copilot está trabalhando nela.

![O Copilot usa o emoji de olhos para indicar que está trabalhando na issue](../../../_images/ex4-issue-eyes-emoji.png)

Agora o Copilot está trabalhando na segunda solicitação. O agente de nuvem do Copilot funciona de maneira semelhante a uma pessoa engenheira de software, então não é necessário monitorá-lo continuamente: revise o resultado quando estiver pronto. Vamos nos concentrar em criar e usar agentes personalizados.

## Resumo e próximos passos

Neste exercício, você explorou o [agente de nuvem do GitHub Copilot][copilot-agents]. Com ele, é possível atribuir issues ao Copilot para execução assíncrona. Você pode usá-lo para resolver dívidas técnicas, criar funcionalidades ou ajudar a migrar código de uma estrutura para outra.

Você explorou estes conceitos:

- personalizar o ambiente para gerar código.
- garantir que as operações sejam realizadas com segurança.
- entender a importância de issues com escopo claro.
- atribuir issues ao Copilot.

Enquanto o agente de nuvem trabalha em segundo plano, vamos criar e usar agentes personalizados. O [agente de nuvem do Copilot também pode usar servidores MCP][cloud-agent-mcp] e as instruções personalizadas disponíveis, que exploramos nos módulos anteriores.

## Recursos

- [Sobre o agente de nuvem do Copilot][copilot-agents]
- [Atribuir issues do GitHub ao Copilot][assign-issue]
- [Práticas recomendadas para o workflow de configuração do agente de nuvem do Copilot][cloud-agent-best-practices]

| [Próxima lição: Agentes personalizados →][next-lesson] |
|--:|

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-custom-agents/
[cloud-agent-mcp]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/extend-cloud-agent-with-mcp
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[github-actions]: https://docs.github.com/actions
