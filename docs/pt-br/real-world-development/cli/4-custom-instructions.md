---
title: "Lição 4 - Oriente o Copilot com instruções personalizadas"
description: "Explore as instruções do repositório, adicione um padrão de documentação e aplique-o ao código de filtragem."
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

O contexto é essencial ao trabalhar com IA generativa. Se uma tarefa precisa ser realizada de uma maneira específica, você quer que o Copilot tenha essa orientação. Os [arquivos de instruções][instruction-files] descrevem não apenas *que* código você quer, mas também *como* ele deve ser estruturado. Agora que você implementou a filtragem, vai explorar as instruções usadas pelo Copilot, adicionar um padrão de documentação e aplicá-lo ao código.

Nesta lição, você vai:

- explorar como as instruções do repositório e os arquivos de instruções específicos de caminhos chegam ao agente.
- atualizar o arquivo de instruções para garantir que os padrões de código sejam seguidos.
- observar o impacto dos arquivos de instruções no código.

## Cenário

Como toda boa empresa de desenvolvimento, a Tailspin Toys tem diretrizes e requisitos para as práticas de desenvolvimento. Eles incluem:

- Os comentários devem explicar a intenção e as decisões que não são óbvias, em vez de repetir o código.
- As funções exportadas em `db/` e `src/lib/` devem documentar sua finalidade, seus parâmetros e valores de retorno com TSDoc/JSDoc, incluindo um argumento `db` injetável quando houver.
- Os componentes Astro reutilizáveis devem documentar seus contratos `Props`, e os comentários devem continuar atualizados quando o código relacionado mudar.
- As orientações existentes de formatação e lint devem ser preservadas.

Com os arquivos de instruções, você garantirá que o Copilot tenha as informações necessárias para realizar tarefas de acordo com as práticas destacadas.

## Arquivos de instruções

As instruções personalizadas fornecem contexto e preferências ao Copilot para que ele entenda melhor seu estilo e seus requisitos de programação. Com elas, você pode orientar as sugestões e os trechos de código para que sejam mais relevantes. É possível criar instruções para todo o repositório ou para tipos específicos de arquivos e tarefas.

Há dois tipos de arquivos de instruções:

- `.github/copilot-instructions.md`: um único arquivo de instruções enviado ao Copilot em **todas** as solicitações feitas no repositório. Ele deve conter informações sobre o projeto relevantes para a maioria das solicitações.
- `.github/instructions/*.instructions.md`: arquivos com diretrizes para linguagens, tipos de arquivo ou tarefas específicas.

> [!NOTE]
> Outros formatos de instrução e o suporte a eles variam conforme o ambiente. Consulte a [referência de suporte a instruções personalizadas][custom-instructions-support] antes de depender de um formato específico.

## Explore os arquivos de instruções personalizadas deste projeto

Para começar, o projeto inicial já inclui alguns arquivos de instruções. Vamos explorá-los antes de fazer uma alteração para observar o impacto.

1. Volte ao Codespace. No editor do Codespaces, abra `.github/copilot-instructions.md`.
2. Explore o arquivo e observe a breve descrição do projeto e as diretrizes de programação. Essas instruções se aplicam a todas as interações com o Copilot neste repositório.
3. Abra a pasta `.github/instructions` e explore os arquivos. Há instruções para arquivos Astro, a camada de dados Drizzle, testes e outros tópicos.
4. Abra `.github/instructions/unit-tests.instructions.md`. Observe o campo `applyTo` no início do arquivo: ele define um padrão glob que determina a quais arquivos as instruções se aplicam.
5. Abra `.github/instructions/drizzle.instructions.md` e observe os links para outros arquivos de instruções e arquivos existentes do projeto. Assim, você pode dividir conjuntos maiores de instruções em arquivos menores e reutilizáveis e indicar exemplos que o Copilot pode seguir.

## Atualize os arquivos de instruções para refletir as orientações da equipe

Os arquivos existentes são um bom começo, mas ainda falta uma orientação. Vamos modificar o arquivo principal `copilot-instructions.md` para garantir que novos arquivos TypeScript tenham comentários TSDoc.

1. Em `.github/copilot-instructions.md`, localize a seção intitulada **Code formatting guidance**, que deve estar perto da linha 35.
2. Adicione o texto a seguir como último item da lista:

   ```markdown
   - All new TypeScript should contain TSDocs comments for documentation purposes.
   ```

O arquivo será salvo automaticamente!

## Use as orientações atualizadas

O Copilot CLI carrega as instruções do repositório quando uma conversa começa. Depois de salvar as instruções atualizadas, saia e retome a conversa de filtragem para que o Copilot use as novas orientações sem perder o contexto do recurso.

1. Se a conversa de filtragem ainda estiver aberta, digite `/exit` para encerrá-la. O Copilot CLI salva as conversas automaticamente.
2. No diretório raiz do repositório e no branch `game-filters-cli`, retome a conversa salva:

   ```bash
   copilot --resume
   ```

   Se for solicitado, selecione a conversa de filtragem e confirme que o branch `game-filters-cli` está selecionado.
3. Peça ao Copilot que aplique as orientações atualizadas:

   ```plaintext
   We just updated our instructions and code guidance. Can you please update the code you generated to match that guidance?
   ```

4. Digite `/diff` e leia os arquivos TypeScript alterados. Observe os comentários TSDoc adicionados e confirme que eles descrevem o código corretamente.

## Resumo e próximos passos

Você explorou como o Copilot CLI obtém contexto dos arquivos de instruções do projeto e aplicou um novo padrão ao recurso. Especificamente, você:

- explorou como as instruções do repositório e os arquivos de instruções específicos de caminhos chegam ao agente.
- atualizou o arquivo de instruções para garantir que os padrões de código sejam seguidos.
- observou o impacto dos arquivos de instruções no código.

Em seguida, você vai [personalizar e executar o skill reutilizável `quality-checks`][next-lesson] para garantir que o lint e os testes sejam executados de maneira consistente.

## Recursos

- [Adicionar instruções personalizadas para o Copilot CLI][instruction-files]
- [Suporte a instruções personalizadas][custom-instructions-support]
- [Práticas recomendadas para criar instruções personalizadas][instructions-best-practices]
- [Awesome Copilot — coleção de arquivos de instruções e outros recursos][awesome-copilot]

[instruction-files]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot/add-custom-instructions
[instructions-best-practices]: https://docs.github.com/copilot/concepts/prompting/response-customization#writing-effective-custom-instructions
[awesome-copilot]: https://awesome-copilot.github.com/
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support
[previous-lesson]: ../3-agent-modes/
[next-lesson]: ../5-agent-skills/
