---
title: "Exercício 1 - Instruções personalizadas (VS Code)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← Lição anterior: Pré-requisitos][previous-lesson] · [Próxima lição: Modo de agente →][next-lesson]

O contexto é essencial ao trabalhar com IA generativa. Se uma tarefa precisa ser realizada de uma maneira específica — ou há informações de contexto que o Copilot deve conhecer —, disponibilize esse contexto. Há várias maneiras de compartilhar informações específicas com o Copilot. Uma das principais são os [arquivos de instruções][instruction-files], que fornecem orientação para a geração de código.

Neste exercício, você vai:

- explorar como o contexto específico do projeto, as diretrizes de programação e os padrões de documentação chegam ao Copilot por meio de instruções personalizadas do repositório e arquivos de instruções específicos de caminhos.
- gerar a primeira parte da camada de dados para filtragem (um auxiliar de editoras) usando as instruções atuais.
- adicionar um novo padrão para todo o repositório em `.github/copilot-instructions.md`.
- repetir o mesmo prompt e observar o código gerado adotar o novo padrão.
- fazer commit das instruções atualizadas e da primeira parte da filtragem no `main` para que o Copilot use as orientações atualizadas no próximo exercício.

> [!CAUTION]
> O código gerado pode não seguir alguns dos padrões definidos. O Copilot é não determinístico. O objetivo deste exercício é observar a *tendência* de mudança no comportamento após a atualização das instruções, não obter um resultado idêntico, caractere por caractere.

## Arquivos de instruções

### Cenário

Como toda boa empresa de desenvolvimento, a Tailspin Toys tem diretrizes e requisitos para as práticas de desenvolvimento. Eles incluem:

- A camada de dados sempre precisa de testes unitários.
- A interface do usuário deve usar o modo escuro e ter uma aparência moderna.
- O código deve incluir documentação na forma de comentários TSDoc.
- Um bloco de comentários no início de cada arquivo deve descrever sua finalidade.

Com os arquivos de instruções, você garantirá que o Copilot tenha as informações necessárias para realizar as tarefas de acordo com essas práticas.

### Instruções personalizadas

As instruções personalizadas fornecem contexto e preferências ao Copilot para que ele entenda melhor seu estilo e seus requisitos de programação. Com elas, você pode orientar as sugestões e os trechos de código para que sejam mais relevantes. É possível especificar convenções de programação, bibliotecas e até os tipos de comentários a incluir no código. Você pode criar instruções para todo o repositório ou para tipos específicos de arquivos e tarefas.

Há dois tipos de arquivos de instruções:

- `.github/copilot-instructions.md`: um único arquivo de instruções enviado ao Copilot em **todas** as solicitações feitas no repositório. Ele deve conter informações sobre o projeto relevantes para a maioria das solicitações de chat ou CLI, como a pilha de tecnologias, uma visão geral do que está sendo desenvolvido, práticas recomendadas e outras orientações globais.
- `.github/instructions/*.instructions.md`: arquivos que podem ser criados para tarefas ou tipos de arquivo específicos. Use-os para fornecer diretrizes para linguagens específicas, como TypeScript ou Astro, ou para tarefas, como criar um componente de interface ou testes unitários.

> [!NOTE]
> Em um IDE, os arquivos de instruções são usados apenas para gerar código no Copilot Chat, não para sugestões de conclusão de código ou de próxima edição.
>
> O Copilot Chat, o Copilot CLI e o agente de nuvem do Copilot usam tanto as instruções do repositório quanto os arquivos `*.instructions.md` com frontmatter `applyTo`.
>
> O Copilot também [oferece suporte a arquivos de instruções em outros padrões][custom-instructions-support], incluindo arquivos AGENTS.md e CLAUDE.md.

### Práticas recomendadas para gerenciar arquivos de instruções

Uma conversa completa sobre a criação de arquivos de instruções está fora do escopo do workshop. No entanto, os exemplos do projeto mostram uma abordagem representativa. Em linhas gerais:

- Mantenha o conteúdo de `copilot-instructions.md` focado nas orientações gerais do projeto, como uma descrição do que está sendo desenvolvido, a estrutura do projeto e os padrões globais de programação.
- Use arquivos `*.instructions.md` para fornecer instruções específicas para tipos de arquivo, como testes unitários, componentes Astro e a camada de dados, ou para tarefas específicas.
- Use linguagem natural e mantenha as orientações claras. Inclua exemplos de como o código deve ou não deve ser escrito.

Não há uma única maneira certa de criar arquivos de instruções, assim como não há uma única maneira de usar IA. Experimente para descobrir o que funciona melhor no seu projeto e nos seus cenários.

> [!TIP]
> Todo projeto que usa o GitHub Copilot deve ter uma coleção consistente de arquivos de instruções. Ao explorar os arquivos deste projeto, talvez você encontre instruções para vários tipos de tarefas, incluindo [atualizações de interface][ui-instructions] e [arquivos Astro][astro-instructions].
>
> O Copilot também pode ajudar a gerar arquivos de instruções. Cada interface oferece essa opção de uma maneira diferente, como **Configure Chat → Generate Agent Instructions** no VS Code ou `/init` no Copilot CLI. A lição da interface utilizada vai explicar o processo quando for relevante.
>
> Para encontrar templates ou um ponto de partida, explore o [awesome-copilot][awesome-copilot], um repositório com arquivos de instruções, agentes personalizados e outros recursos.

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## Explore os arquivos de instruções personalizadas deste projeto

Leia os arquivos de instruções incluídos neste repositório. Há um arquivo principal, `copilot-instructions.md`, e vários arquivos `*.instructions.md` para tarefas diferentes. Abra-os no editor ou na interface Web do GitHub.

1. Abra `.github/copilot-instructions.md`.
2. Explore o arquivo e observe a breve descrição do projeto e seções como **Agent notes**, **Code standards**, **Scripts** e **Repository Structure**. Em **Code standards**, observe as orientações aninhadas sobre **GitHub Actions Workflows**. Elas se aplicam a todas as interações com o Copilot.
3. Abra a pasta `.github/instructions` e explore os arquivos. Há instruções para arquivos Astro, a camada de dados Drizzle, testes e outros tópicos.
4. Abra `.github/instructions/unit-tests.instructions.md`. Observe o campo `applyTo` no frontmatter. Ele define um padrão glob relativo à raiz do repositório para determinar a quais arquivos as instruções se aplicam. Neste caso, correspondem a arquivos de teste TypeScript, como os que seguem o padrão `**/*.test.ts`.
5. Observe as instruções específicas para a criação de testes unitários neste projeto.
6. Abra `.github/instructions/drizzle.instructions.md` e vá até o final. Observe os links para outros arquivos de instruções, como `unit-tests.instructions.md`, e para arquivos existentes do projeto. Assim, você pode dividir conjuntos maiores de instruções em arquivos menores e reutilizáveis e indicar exemplos que o Copilot pode seguir ao gerar código. Os caminhos são relativos ao arquivo de instruções, não à raiz do repositório.

> [!NOTE]
> A seção **Code formatting requirements** em `copilot-instructions.md` documenta os padrões de programação do projeto, mas ainda não exige documentação no código. Na próxima etapa, você adicionará regras para comentários TSDoc e cabeçalhos de comentários nos arquivos.

## Crie um branch para as alterações

Vamos seguir algumas práticas recomendadas e criar um branch para as alterações.

1. Volte ao Codespace usado no exercício anterior.
2. Abra um novo terminal pressionando <kbd>Control</kbd>+<kbd>`</kbd> (Mac) ou <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux).
3. Crie e selecione um novo branch:

   ```bash
   git checkout -b custom-instructions
   ```

## Use o Copilot Chat *antes* de atualizar as instruções

> [!TIP]
> **Abra o Copilot Chat**
>
> Antes de começar os exercícios abaixo, volte ao Codespace, abra o painel Copilot Chat e selecione **New Chat** para iniciar uma conversa limpa. O modo e o modelo variam conforme o exercício; cada etapa informa o que selecionar quando necessário.

Para observar o impacto das instruções personalizadas, primeiro envie um prompt com o arquivo de instruções atual. Depois, atualize-o e envie o mesmo prompt para comparar o resultado.

1. Feche as guias de editor abertas nos exercícios anteriores para que o Copilot receba apenas o contexto desejado.
2. Abra `src/lib/publishers.ts` para indicar ao Copilot onde o auxiliar deve ficar.
3. Selecione **Agent** no seletor de agentes da exibição Chat para permitir que o Copilot altere arquivos.

   ![Seletor de agente na exibição Chat](../../../_images/shared-chat-mode-selector.png)

4. Envie o prompt a seguir:

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

5. O Copilot explora o projeto e aplica as alterações no código, geralmente no arquivo do auxiliar e nos testes.
6. Observe que o auxiliar proposto é uma função tipada que recebe um cliente `db` como primeiro argumento e retorna um array tipado de editoras. Isso segue as convenções da camada de dados em `.github/instructions/drizzle.instructions.md`, aplicáveis a `src/lib/*.ts`.
7. Observe que o código proposto **não tem** comentários TSDoc nem cabeçalho de comentários no arquivo.

> [!CAUTION]
> Como o Copilot é probabilístico, talvez ele adicione comentários de documentação mesmo sem essa orientação. Tudo bem: o objetivo é observar a melhoria na *consistência* depois da atualização das instruções.

## Adicione um novo padrão ao repositório

Como vimos anteriormente, `.github/copilot-instructions.md` fornece informações do projeto ao Copilot. Vamos documentar os padrões de programação do repositório para melhorar as sugestões de código.

1. Abra `.github/copilot-instructions.md` novamente.
2. Localize a seção **Code formatting requirements**, que deve estar perto da linha 27. Observe como ela documenta os padrões de programação do projeto, mas ainda não contém uma regra para documentação no código. Por isso, o auxiliar gerado não tinha comentários de documentação.
3. Adicione as linhas Markdown a seguir logo abaixo dos padrões existentes para instruir o Copilot a adicionar cabeçalhos de comentários nos arquivos e comentários TSDoc:

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. Salve `copilot-instructions.md`.

> [!TIP]
> Como você viu na lição anterior, os arquivos de instruções podem ser criados na raiz do repositório (`.github/copilot-instructions.md`) para orientar o projeto inteiro ou como arquivos `*.instructions.md` para linguagens, tipos de arquivo ou tarefas específicas. O arquivo do repositório é o lugar certo para padrões gerais, como a regra de comentários de documentação que você acabou de adicionar.

## Repita o prompt e observe a mudança

1. Volte ao Copilot Chat e selecione **New Chat** para limpar o contexto.
2. Selecione `src/lib/publishers.ts` novamente para que o Copilot se concentre no arquivo correto.
3. Envie o **mesmo prompt** usado antes:

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

4. Observe que o arquivo proposto agora começa com um bloco de comentários semelhante a este:

   ```typescript
   /**
    * Publisher data-access helpers for the Tailspin Toys Crowd Funding platform.
    * Provides functions to retrieve publisher information from the database.
    */
   ```

5. Observe que a função proposta agora inclui um comentário TSDoc semelhante a este:

   ```typescript
   /**
    * Returns a list of all publishers with their id and name.
    *
    * @param db - The Drizzle database client.
    * @returns A promise that resolves to an array of publisher objects.
    */
   ```

Você orientou o Copilot a seguir um novo padrão e aplicá-lo ao código real que servirá de base para o próximo exercício.

## Faça commit das instruções e envie o branch

Os arquivos de instruções são recursos do repositório e devem ser gerenciados com o mesmo processo de controle do código-fonte. Vamos fazer commit e enviar o branch.

1. Abra uma nova janela de terminal pressionando <kbd>Control</kbd>+<kbd>`</kbd> (Mac) ou <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux).
2. Confirme se as instruções atualizadas e as alterações do auxiliar estão presentes:

   ```bash
   git status
   ```

3. Prepare e faça commit da atualização das instruções e de todos os arquivos alterados pelo Copilot para a base do auxiliar:

   ```bash
   git add .github/copilot-instructions.md src/lib/publishers.ts
   # Se o git status mostrar outras atualizações relacionadas (por exemplo, testes), adicione esses arquivos também.
   git commit -m "Add doc comment standards and publishers helper foundation"
   ```

4. Envie o branch para o repositório:

   ```bash
   git push -u origin custom-instructions
   ```

## Crie e mescle um pull request

Com o branch enviado, crie um pull request e associe-o à issue sobre o padrão de documentação no backlog. O Copilot pode fazer isso usando as ferramentas do GitHub já conectadas ao projeto. Vamos pedir que localize a issue, crie o PR associado a ela e depois faça a mesclagem.

> [!NOTE]
> Este é o primeiro exercício em que o Copilot executa ações no GitHub em seu nome. O template do projeto já conecta as ferramentas do GitHub ao workspace, então não é necessário configurá-las. Na primeira vez que o Copilot usar uma delas, o VS Code talvez peça que você entre no GitHub. Siga as instruções para autorizá-lo. Você aprenderá como essa conexão funciona (Model Context Protocol) em um exercício posterior.

1. Abra o Copilot Chat no Codespace.
2. Pressione <kbd>Control</kbd>+<kbd>Command</kbd>+<kbd>I</kbd> (Mac) ou <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>I</kbd> (Windows/Linux) para abrir a exibição Copilot Chat e confirme que **Agent** está selecionado no seletor de agentes.
3. Peça ao Copilot para localizar a issue sobre a atualização dos arquivos de instruções e criar um PR a partir do branch atual, descrevendo tanto as atualizações das instruções quanto a base do auxiliar de editoras:

   ```plaintext
   Find the issue related to updating the instructions file. Create a new PR from the current branch, highlight that the PR closes that issue, and include that we also added the publishers helper foundation for the upcoming filtering work.
   ```

4. O Copilot começará a localizar a issue e criar o PR.
5. Quando solicitado a permitir que o Copilot execute ações no GitHub em seu nome, revise o comando e selecione **Allow** se estiver de acordo.
6. Depois da criação do PR, peça ao Copilot que o mescle e retorne seu branch local para `main`:

   ```plaintext
   Merge the PR into main. Then return to main locally, and pull the latest code so we are up to date.
   ```

7. Quando solicitado a permitir ações no GitHub e comandos de shell em seu nome, revise os comandos e selecione **Allow** se estiver de acordo.

Você criou e mesclou um pull request com a ajuda do GitHub Copilot!

## Resumo e próximos passos

Você explorou como o Copilot obtém contexto dos arquivos de instruções deste projeto e usou o Copilot Chat no VS Code para:

- enviar um prompt de geração de código e observar o resultado com as instruções *atuais*.
- adicionar um novo padrão para todo o repositório em `.github/copilot-instructions.md`.
- repetir o mesmo prompt e observar o código proposto adotar o novo padrão.
- fazer commit das instruções e da base do auxiliar no `main` para que o próximo exercício possa usá-las.

Em seguida, você usará as instruções no [modo de agente][next-lesson], enquanto o Copilot adiciona um novo recurso à base de código.

## Recursos

- [Arquivos de instruções para personalizar o GitHub Copilot][instruction-files]
- [Práticas recomendadas para criar instruções personalizadas][instructions-best-practices]
- [Cinco dicas para escrever instruções personalizadas melhores para o Copilot][copilot-instructions-five-tips]
- [Instruções pessoais personalizadas para o GitHub Copilot][personal-instructions]
- [Awesome Copilot — coleção de arquivos de instruções e outros recursos][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-agent-mode/
[instruction-files]: https://code.visualstudio.com/docs/copilot/copilot-customization
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[personal-instructions]: https://docs.github.com/copilot/customizing-copilot/adding-personal-custom-instructions-for-github-copilot
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
[awesome-copilot]: https://github.com/github/awesome-copilot
