---
title: "Lição 10 - Recapitulação e próximos passos"
description: "Recapitule o fluxo de trabalho do Copilot CLI, os dois pull requests, as personalizações reutilizáveis e outros recursos."
authors:
  - geektrainer
lastUpdated: 2026-09-29
---

Você usou o GitHub Copilot CLI em um fluxo contínuo de trabalho no Tailspin Toys. Você:

- preparou um Codespace, instalou o Copilot CLI, explorou o projeto e encontrou a issue de filtragem do backlog.
- adicionou avaliações por estrelas, revisou o resultado em um navegador encaminhado e mesclou manualmente seu primeiro pull request (PR).
- começou pela issue de filtragem, definiu a abordagem no modo Plan, desenvolveu o recurso no modo Autopilot e o revisou no modo Interactive.
- orientou o agente com instruções personalizadas, personalizou o skill `quality-checks` e o usou para executar testes unitários, lint e verificações de tipos.
- adicionou o servidor Model Context Protocol (MCP) do Playwright e o usou para explorar a filtragem em um navegador real.
- criou e selecionou um agente personalizado de garantia de qualidade (QA) para avaliar requisitos, cobertura, resultados do skill e evidências do navegador.
- revisou a alteração completa do recurso e autorizou o Agent Merge para o PR de filtragem.
- explorou comandos de barra para gerenciar o contexto, os modelos e o compartilhamento e, se quiser, delegar tarefas ao agente na nuvem.

## O que você entregou

O workshop tem dois marcos de PR, cada um em seu próprio branch criado a partir do `main` atualizado:

1. **Avaliações por estrelas:** exiba `starRating` e um estado explícito para jogos sem avaliação nos cards.
2. **Filtragem e fluxo de qualidade:** implemente a filtragem, atualize as instruções e aplique-as ao recurso, personalize o relatório do skill `quality-checks`, crie um perfil de QA e inclua os testes relacionados.

Do planejamento da filtragem até a abertura do PR, você usou a mesma conversa e o mesmo branch. Para simplificar o workshop, reunimos todo esse trabalho em um único PR.

## Diferentes tipos de verificação

Você verificou o código de várias maneiras: testes automatizados, inspeção no navegador e exploração do navegador pelo Copilot usando MCP. O skill `quality-checks` executou testes unitários, lint e verificações de tipos e apresentou os resultados no novo formato. O QA reuniu esses resultados com a revisão dos requisitos e da cobertura de testes antes da abertura do PR.

Os testes adicionados devem preencher lacunas reais; uma execução de QA que não precisa de testes novos também pode estar correta. Revise o código e as evidências antes de autorizar a mesclagem e atualize as evidências afetadas depois de fazer alterações.

## Práticas recomendadas

O contexto e as ferramentas fornecidos ao Copilot influenciam o trabalho dele. Neste workshop, você atualizou instruções, personalizou um skill, criou um perfil de QA e configurou um servidor MCP. Reutilize essas personalizações em outras conversas e ajuste-as conforme as necessidades da equipe. As instruções definem padrões, os skills descrevem tarefas repetíveis, os agentes personalizados definem funções especializadas e os servidores MCP conectam ferramentas externas. Revise as alterações e os resultados das ferramentas, não apenas o resumo do agente.

Escolha o **modo e o modelo** de acordo com a tarefa. Use **Plan** para pensar na abordagem antes de começar, **Interactive** para acompanhar de perto alterações específicas e **Autopilot** para tarefas com escopo bem definido. Escolha um modelo mais rápido para edições rotineiras e um modelo mais avançado para tarefas complexas.

O contexto continua sendo tão importante quanto a infraestrutura. Descrever com clareza *o que* você quer desenvolver, *por que* e *como* influencia significativamente o resultado.

## Outros recursos para explorar

Você concluiu o fluxo de trabalho principal. Confira outros recursos do CLI:

- `/review` para pedir ao agente de revisão de código que analise as alterações.
- `/rubber-duck` para discutir um problema e obter outra perspectiva.
- `/fleet` para coordenar subtarefas independentes em paralelo.
- `/worktree` para isolar uma tarefa.
- `/delegate` para enviar uma tarefa ao agente de nuvem do Copilot.

## Próximos passos

A melhor maneira de se aprimorar em qualquer ferramenta é continuar usando-a! Use-a em código de produção, em projetos pessoais ou naquele pequeno aplicativo que você imagina há anos, mas ainda não teve tempo de desenvolver. Compartilhe seus aprendizados com a equipe e aprenda com os outros. E, como sempre, explore a documentação.

Para ampliar o Tailspin Toys pelo terminal, continue com a série opcional [Backer Concierge com o Foundry][foundry]. Para comparar outros ambientes, explore o [workshop do VS Code][vscode], o [workshop do aplicativo GitHub Copilot][app] ou o [workshop do agente de nuvem do Copilot][cloud].

## Recursos

- [Sobre o GitHub Copilot CLI][about-cli]
- [Referência de comandos do Copilot CLI][cli-reference]
- [Personalizar o Copilot CLI][customize-cli]
- [Gerenciar pull requests com o Copilot CLI][manage-prs]

[previous-lesson]: ../9-cli-power-tools/
[foundry]: ../8-foundry-agent/
[vscode]: ../../vscode/
[app]: ../../app/
[cloud]: ../../cloud/
[about-cli]: https://docs.github.com/copilot/concepts/agents/about-copilot-cli
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[customize-cli]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot
[manage-prs]: https://docs.github.com/copilot/how-tos/copilot-cli/use-copilot-cli/manage-pull-requests
