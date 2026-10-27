---
title: "Lição 5 - Personalize e use um skill quality-checks"
description: "Explore o skill quality-checks existente, personalize o formato do relatório e use-o para validar a filtragem."
authors:
  - geektrainer
lastUpdated: 2026-09-29
---

Escrever código envolve mais do que apenas escrever código. Já validamos manualmente se o código funciona e usamos arquivos de instruções para garantir que ele siga nossos padrões. E quanto aos testes, ao lint e às outras partes da integração contínua (CI)?

Para esses tipos de tarefa, os **skills de agente** são ideais. Eles ajudam o Copilot a entender como executar operações como essas.

Nesta lição, você vai:

- explorar o skill existente `quality-checks`.
- personalizar o formato dos resultados.
- recarregar e executar o skill.

## Cenário

A Tailspin Toys usa o skill `quality-checks` para testes unitários, lint e verificações de tipos. A equipe quer melhorar o relatório para facilitar a leitura dos resultados.

## Instruções, scripts e recursos

Os skills de agente reúnem instruções reutilizáveis para tarefas, scripts executáveis e recursos de apoio que um agente carrega quando necessário. Em sua forma básica, um skill é uma pasta com o nome dele e um arquivo Markdown chamado `SKILL.md`. O Markdown tem frontmatter com nome e descrição para definir a finalidade do skill, uma visão geral do que ele faz e orientações sobre quando deve ser chamado. A pasta também pode conter subpastas com scripts e outros recursos usados pelo skill.

> [!NOTE]
> Um skill não precisa de outros arquivos nem pastas. O skill `quality-checks` do Tailspin Toys contém apenas `SKILL.md`, pois usa os comandos existentes no projeto.

Os skills podem ficar na pasta `.github/skills` de um projeto para serem compartilhados e reutilizados pela equipe ou na pasta de skills do usuário, `~/.copilot/skills`.

## Explore o skill

Vamos explorar o skill que a equipe do Tailspin Toys criou para executar testes unitários, lint e verificações de tipos, chamado `quality-checks`.

1. Volte ao Codespace. No editor do Codespaces, abra `.github/skills/quality-checks/SKILL.md`.
2. Leia o `name` e a `description` no início do arquivo. A descrição ajuda o Copilot a entender quando deve chamar o skill.
3. Leia as instruções e observe como elas orientam o Copilot durante os testes e o lint.
4. Observe que o skill ainda não tem uma seção **Results output formatting**.

## Execute o skill antes de fazer alterações

Os skills podem ser chamados diretamente pelo Copilot CLI ou por meio de linguagem natural. Vamos pedir ao Copilot que execute as três verificações do skill.

1. Volte à conversa de filtragem no modo Interactive.
2. Use este prompt:

   ```plaintext
   Run the quality-checks skill for unit tests, lint, and type checks.
   ```

3. Observe o relatório final.

## Personalize o relatório

Queremos um relatório melhor, que informe o que foi executado, se houve aprovação e o que as ferramentas relataram. Vamos atualizar o skill para gerar esse relatório.

1. Volte a `.github/skills/quality-checks/SKILL.md`.
2. Adicione a seção a seguir ao final do arquivo:

   ```markdown
   ## Results output formatting

   Upon completion, report each command that ran and whether it passed, failed, or was blocked. Include test counts, durations, errors, warnings, and other metrics only when the tool reports them. Identify the next action for any failure or blocker, and never describe a skipped or incomplete check as passed.
   ```

3. O arquivo será salvo automaticamente.

## Execute o skill atualizado

Agora que fizemos a alteração, vamos ver o resultado. O Copilot CLI pode recarregar skills editados sem reiniciar a conversa.

1. Digite:

   ```plaintext
   /skills reload
   ```

2. Use exatamente o mesmo prompt anterior:

   ```plaintext
   Run the quality-checks skill for unit tests, lint, and type checks.
   ```

3. Observe o relatório final e compare-o com o primeiro.

## Resumo e próximos passos

Você personalizou e usou um skill de agente existente. Nesta lição, você:

- explorou o skill `quality-checks` para testes unitários, lint e verificações de tipos.
- personalizou o formato dos resultados.
- recarregou e executou o skill.

Essa alteração acompanhará a filtragem no PR do recurso. Em seguida, você permitirá que o Copilot interaja diretamente com o site [usando o servidor MCP do Playwright][next-lesson].

## Mais exemplos de skills

Estes exemplos da comunidade servem como referência, não como tarefas adicionais:

- [Especificação de Agent Skills][skill-spec]
- [Workflow de contribuição: `make-repo-contribution`][contribution-example]
- [Documentos de requisitos: `prd`][prd-example]
- [Diagramas e script de exportação incluído: `drawio`][drawio-example]
- [Testes de navegador: `webapp-testing`][browser-example]

[previous-lesson]: ../4-custom-instructions/
[next-lesson]: ../6-mcp-playwright/
[skill-spec]: https://agentskills.io/specification
[contribution-example]: https://github.com/github/awesome-copilot/tree/main/skills/make-repo-contribution
[prd-example]: https://github.com/github/awesome-copilot/tree/main/skills/prd
[drawio-example]: https://github.com/github/awesome-copilot/tree/main/skills/drawio
[browser-example]: https://github.com/github/awesome-copilot/tree/main/skills/webapp-testing
