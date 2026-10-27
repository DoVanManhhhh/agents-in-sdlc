---
title: "Exercício 2 - Adicione funcionalidades com o modo de agente do Copilot"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

Até mesmo uma atualização simples de um aplicativo costuma envolver vários arquivos e operações, como executar testes. Em geral, a pessoa desenvolvedora localiza os arquivos necessários, faz as alterações, executa os testes, depura, descobre qual arquivo faltou, faz outra alteração... E assim por diante.

É aí que entra o modo de agente do Copilot.

O modo de agente do Copilot foi criado para atuar com mais autonomia no IDE. Ele funciona de maneira semelhante a uma pessoa desenvolvedora: começa explorando a estrutura existente do projeto, faz as alterações necessárias, executa tarefas como testes e corrige automaticamente os problemas encontrados. Vamos explorar como usar o modo de agente para adicionar uma nova funcionalidade ao site.

> [!NOTE]
> Embora os nomes sejam parecidos, o modo de agente e o agente de nuvem oferecem experiências diferentes. O modo de agente executa tarefas no IDE, com ciclos rápidos de feedback e interação. O agente de nuvem funciona como um parceiro de programação que trabalha de forma assíncrona, interagindo com você por meio de issues e pull requests.

Neste exercício, você vai aprender como:

- o modo de agente do Copilot explora o projeto, identifica os arquivos relevantes e coordena as alterações.
- o modo de agente do GitHub Copilot implementa funcionalidades na interface e na camada de dados.
- revisar as alterações e os testes gerados pelo modo de agente do Copilot antes de mesclá-los à base de código.

## Cenário

À medida que a lista de jogos cresce, você quer permitir que as pessoas filtrem os jogos por categoria e editora. No exercício anterior, você adicionou um auxiliar de editoras. Agora, concluirá o trabalho restante na camada de dados, na interface e nos testes com o modo de agente do Copilot.

## Execute o site Tailspin Toys

Antes de fazer alterações, explore o site Tailspin Toys para entender a funcionalidade atual.

O site é uma plataforma de financiamento coletivo para jogos de tabuleiro com um tema de desenvolvimento. Ele permite listar jogos e exibir detalhes. O site é um único aplicativo Astro que renderiza páginas como HTML estático durante a compilação. As páginas consultam diretamente um banco de dados SQLite local no frontmatter, usando o ORM Drizzle. Não há uma API de back-end separada nem um framework de interface executado no cliente. Os auxiliares reutilizáveis de acesso a dados ficam em `src/lib/`, e a interatividade é adicionada com um pequeno `<script>` do Astro, específico para a página, que usa APIs padrão do DOM.

### Inicie o site

Para facilitar a execução do site, há uma tarefa `npm run dev` que inicia o único servidor de desenvolvimento Astro. Siga estas etapas para executá-la no GitHub Codespace:

1. Volte ao Codespace. Você deve estar no `main` depois do exercício anterior.
2. Abra uma nova janela de terminal no Codespace pressionando <kbd>Control</kbd>+<kbd>\`</kbd> (Mac) ou <kbd>Ctrl</kbd>+<kbd>\`</kbd> (Windows/Linux).
3. Crie e selecione um branch para o trabalho de filtragem:

   ```bash
   git checkout main
   git pull
   git checkout -b filtering-vscode
   ```

4. Execute o comando a seguir para iniciar o site:

   ```bash
   npm run dev
   ```

   Quando o servidor de desenvolvimento Astro estiver pronto, você verá um aviso com a URL, semelhante a:

   ```bash
   🚀 Tailspin Toys is ready!
      Astro server: http://localhost:4321
      Press Ctrl-C to stop.
   ```

> [!NOTE]
> Se uma caixa de diálogo pedir para abrir uma janela do navegador para `http://localhost:4321`, feche-a selecionando o **x**.

5. Abra o site mantendo pressionada a tecla <kbd>Command</kbd> (Mac) ou <kbd>Ctrl</kbd> (Windows/Linux) e selecionando o endereço do servidor Astro `http://localhost:4321` no terminal.

> [!NOTE]
> Em um Codespace, selecionar o link `localhost` no terminal redireciona automaticamente para `https://<your-codespace-name>-4321.app.github.dev/`. Esse é um túnel privado para o Codespace, que agora hospeda o servidor Web.

### Explore o site

Com o site em execução, explore suas funcionalidades principais:

- **Página inicial**: exibe uma lista de jogos de tabuleiro com títulos, imagens e descrições.
- **Página de detalhes do jogo**: ao selecionar um jogo, você acessa uma página de detalhes com mais informações, incluindo título, descrição, editora e categoria.

## Explore o backlog com o Copilot

> [!TIP]
> **Abra o Copilot Chat**
>
> Antes de começar os exercícios abaixo, volte ao Codespace, abra o painel Copilot Chat e selecione **New Chat** para iniciar uma conversa limpa. O modo e o modelo variam conforme o exercício; cada etapa informa o que selecionar quando necessário.

A implementação inicial do site funciona, mas queremos melhorá-la com novos recursos. Vamos começar revisando o backlog. Ao criar o projeto a partir do template, um backlog de issues foi criado automaticamente. Peça ao GitHub Copilot que mostre esses itens.

1. Selecione **Agent** no seletor de agentes da exibição Chat. O agente trabalha de forma autônoma: planeja e implementa alterações em vários arquivos, executa comandos de terminal e chama ferramentas.

   ![Seletor de agente na exibição Chat](../../../_images/shared-chat-mode-selector.png)

2. Selecione **Claude Sonnet 4.5** na lista de modelos disponíveis.

> [!CAUTION]
> As pessoas autoras deste workshop não estão recomendando um modelo em particular. Durante a criação do workshop, usamos o Claude Sonnet 4.5 e o incluímos nas instruções para que as sugestões fossem relativamente consistentes e a experiência fosse boa. No entanto, como os LLMs são probabilísticos, talvez as sugestões recebidas sejam diferentes das apresentadas no workshop. Isso é normal e esperado.

> [!NOTE]
> Devido à natureza probabilística dos LLMs, o Copilot pode usar um comando MCP diferente, mas ainda deverá conseguir concluir a tarefa.

3. Peça ao Copilot que mostre o backlog de issues com o prompt:

   ```plaintext
   Please show me the backlog of items from my GitHub repository. Help me prioritize them based on those which will be most useful to the user.
   ```

4. Selecione **Continue** para permitir a execução do comando que lista todas as issues.
5. Revise a lista gerada.

Observe que o Copilot também priorizou os itens de acordo com o que considera mais útil para as pessoas usuárias.

## Revise os arquivos de instruções

Antes de pedir ao agente que gere código, revise o arquivo de instruções que fornecerá contexto ao Copilot. Você usará o arquivo de instruções da [interface do usuário (UI)](https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md), que descreve como adicionar funcionalidades ao site.

1. No Codespace, acesse `.github/instructions/ui.instructions.md`.
2. Observe as orientações gerais para adicionar funcionalidades, incluindo:
   - uma visão geral da arquitetura.
   - princípios de design de componentes, testabilidade e acessibilidade.
   - links para arquivos de instruções específicos de tipos de arquivo, incluindo:
     - Astro.
     - Tailwind CSS.
     - Drizzle.

> [!TIP]
> Os arquivos de instruções podem fazer referência a outros arquivos de instruções e arquivos do projeto. Os caminhos são relativos ao local do arquivo de instruções. Assim, é possível reutilizar orientações, dividir conjuntos complexos em partes menores e apontar para exemplos e templates.

## Implemente a funcionalidade de filtragem

Para concluir a filtragem, são necessárias pelo menos três alterações separadas no aplicativo:

- adicionar ou aprimorar a lógica de filtragem restante na camada de dados (`src/lib/`).
- adicionar ou atualizar testes do comportamento de filtragem.
- atualizar a página que lista os jogos para incluir a interface de filtragem.

Além disso, os testes precisam ser executados e aprovados antes da mesclagem. O modo de agente do Copilot pode executar essas tarefas. Vamos adicionar a funcionalidade.

1. Continue na conversa atual com o Copilot ou selecione **New Chat** para iniciar outra.
2. Selecione **Add Context**, **Instructions** e **ui** para adicionar o arquivo de instruções.

   ![Exemplo de seleção do arquivo de instruções da interface](../../../_images/ex3-select-instructions-file.png)

3. Confirme se **Agent** continua selecionado no seletor de agentes da exibição Chat.

   ![Seletor de agente na exibição Chat](../../../_images/shared-chat-mode-selector.png)

4. Confirme se **Claude Sonnet 4.5** continua selecionado como modelo.
5. Peça ao Copilot para implementar a funcionalidade com base na issue relacionada do backlog:

   ```plaintext
   Please update the site to include filtering by publisher and category based on the requirements from the related GitHub issue in the backlog. A publishers helper already exists from the previous exercise, so preserve and refine that work as needed while completing the remaining data-layer, UI, and tests. Ensure all tests are passing before completion. The server is already running, so you do not need to start it up.
   ```

6. Observe o Copilot explorar o projeto e localizar os arquivos relacionados à funcionalidade, tanto na camada de dados e na interface quanto nos testes. Em seguida, ele modifica os arquivos e executa os testes.

   ![Copilot explorando os arquivos do projeto](../../../_images/ex3-agent-mode-explores.png)

> [!NOTE]
> O Copilot executará várias tarefas, como explorar o projeto, modificar arquivos e executar testes. Isso pode levar alguns minutos, conforme a complexidade da tarefa e da base de código. Durante o processo, talvez apareçam os controles **Keep** e **Undo** no editor. Quando o Copilot terminar, você verá um desses controles para cada alteração; não é necessário selecioná-los enquanto o trabalho está em andamento.

7. Quando solicitado pelo Copilot, selecione **Continue** para executar os testes.

   ![Caixa de diálogo do Copilot Chat pedindo confirmação para executar testes](../../../_images/ex3-agent-mode-run-tests.png)

8. Talvez haja pausas e alguns testes falhem durante o processo. Tudo bem: o Copilot alterna entre gerar código e executar testes até concluir a tarefa e não detectar erros.

   ![Sessão completa do Copilot Chat no modo de agente](../../../_images/ex3-agent-mode-proposed-changes.png)

9. Explore o código gerado e procure possíveis problemas.

> [!CAUTION]
> Lembre-se: é importante revisar o código gerado pelo Copilot ou por qualquer outra ferramenta de IA.

10. Volte ao navegador em que o site está em execução e explore a nova funcionalidade.
11. Quando confirmar que tudo funciona e terminar de revisar o código, selecione **Keep** na janela do Copilot Chat.

## Resumo e próximos passos

Parabéns! Neste exercício, exploramos como usar o modo de agente do GitHub Copilot para adicionar recursos ao site Tailspin Toys. Aprendemos como:

- o modo de agente do GitHub Copilot implementa funcionalidades na interface e na camada de dados.
- o modo de agente do Copilot explora o projeto, identifica os arquivos relevantes e coordena as alterações.
- revisar as alterações e os testes gerados pelo modo de agente do Copilot antes de mesclá-los à base de código.

Agora vamos [testar o recurso com o servidor MCP do Playwright][next-lesson] e abrir um pull request.

### Exercício extra de exploração: implemente paginação

À medida que a lista de jogos cresce, será necessário adicionar paginação. Use as habilidades deste exercício e peça ao Copilot que implemente a paginação no site. Considere:

- seguir as práticas recomendadas existentes, inclusive usar os arquivos de instruções.
- decidir como implementar a paginação: permitir que a pessoa escolha o tamanho da página ou definir esse valor no código.
- fornecer no prompt as orientações necessárias para que o Copilot implemente a solução desejada.
- iterar com o GitHub Copilot, solicitando alterações e fornecendo contexto. Esse é o fluxo normal de trabalho com o Copilot.

## Recursos

- [Modos ask, edit e agent do Copilot: o que fazem e quando usar cada um][choose-mode]
- [Modo de agente no VS Code][vs-code-agent-mode]

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-mcp/
[choose-mode]: https://github.blog/ai-and-ml/github-copilot/copilot-ask-edit-and-agent-modes-what-they-do-and-when-to-use-them/
[vs-code-agent-mode]: https://code.visualstudio.com/docs/copilot/chat/chat-agent-mode
