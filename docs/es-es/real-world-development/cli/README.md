---
slug: es-es/real-world-development/cli
title: "GitHub Copilot CLI"
description: "Crea, verifica y entrega dos cambios de Tailspin Toys mientras aprendes los modos, las personalizaciones, las herramientas MCP y la automatización de solicitudes de incorporación de cambios de Copilot CLI."
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

**[GitHub Copilot CLI](https://docs.github.com/copilot/concepts/agents/about-copilot-cli)** incorpora GitHub Copilot a tu terminal como asistente de programación con agentes. Explora bases de código, genera código, ejecuta comandos y se conecta a herramientas externas, todo desde la línea de comandos, para que puedas seguir trabajando sin cambiar a un editor gráfico.

El taller recorre un flujo de trabajo continuo en Tailspin Toys:

1. Prepararás el proyecto en GitHub Codespaces, instalarás Copilot CLI y te familiarizarás con él.
2. Añadirás valoraciones con estrellas, revisarás el resultado en el navegador y fusionarás manualmente tu primera solicitud de incorporación de cambios (PR).
3. Partirás de la incidencia de filtrado, definirás el enfoque en modo Plan, lo implementarás en modo Autopilot y lo revisarás en modo Interactive.
4. Actualizarás las instrucciones del repositorio y las aplicarás al trabajo de filtrado.
5. Personalizarás la habilidad existente `quality-checks` y la usarás para ejecutar las comprobaciones del proyecto.
6. Añadirás el servidor Model Context Protocol (MCP) de Playwright y lo usarás para explorar el filtrado en un navegador.
7. Crearás un agente personalizado de control de calidad (QA) para revisar los requisitos, la cobertura y las pruebas de verificación.
8. Revisarás todos los cambios del filtrado y usarás Agent Merge para fusionar su PR.
9. Explorarás comandos de barra para gestionar el contexto y los modelos, compartir sesiones y delegar tareas opcionalmente en la nube.

Para simplificar el taller, crearás dos PR: una para las valoraciones con estrellas y otra para el filtrado con las actualizaciones de instrucciones, la habilidad, el perfil de QA y las pruebas. El filtrado y el flujo de calidad comparten una conversación y una rama para que puedas ampliar el trabajo a medida que exploras cada herramienta.

## Lecciones

| Lección | Tema | Descripción |
| ------ | ----- | ----------- |
| [0. Requisitos previos][ex0] | Configuración | Crea el repositorio y el Codespace |
| [1. Instalar Copilot CLI][ex1] | Instalación | Instala y autentica Copilot CLI y familiarízate con la herramienta |
| [2. Añadir valoraciones con estrellas: una mejora rápida][ex2] | Primer cambio | Muestra las valoraciones existentes y el estado sin valoración; después, fusiona tu primera PR |
| [3. Modos de agente: Plan y Autopilot][ex3] | Modos de agente | Planifica la funcionalidad desde su incidencia, créala con Autopilot y revísala en modo Interactive |
| [4. Guiar a Copilot con instrucciones personalizadas][ex4] | Contexto | Explora y actualiza las instrucciones y aplícalas al filtrado |
| [5. Personalizar y usar una habilidad quality-checks][ex5] | Comprobaciones repetibles | Explora la habilidad existente, cambia el formato del informe y ejecútala |
| [6. Validar la funcionalidad con Playwright MCP][ex6] | Exploración del navegador | Configura MCP en la CLI e inspecciona el filtrado |
| [7. Crear y usar un agente de QA][ex7] | Requisitos y cobertura | Crea y selecciona un perfil especializado y reúne las pruebas finales de verificación |
| [8. Crear y fusionar la PR de la funcionalidad][ex8] | Revisión y fusión | Revisa todos los cambios, crea la PR y usa Agent Merge |
| [9. Comandos de barra de GitHub Copilot CLI][ex9] | Funciones de CLI | Explora el contexto, los modelos, el uso compartido y la delegación opcional en el agente en la nube |
| [10. Resumen y siguientes pasos][ex10] | Resumen | Repasa el flujo, las personalizaciones reutilizables y otros recursos |
| [Opcional: Incorporar Foundry][foundry] | Agentes hospedados | Prepara un modelo, publica un agente basado en un catálogo y conéctalo al sitio |

## Requisitos previos

Antes de asistir a este taller, asegúrate de tener:

- [ ] Una cuenta de GitHub con un plan activo de **Copilot Student, Pro, Pro+, Business o Enterprise**
- [ ] Permiso para crear un repositorio y un Codespace
- [ ] Conocimientos básicos de operaciones de terminal/línea de comandos
- [ ] Git instalado y configurado

> [!TIP]
> ¿No tienes un plan de pago? Los estudiantes verificados pueden obtener GitHub Copilot gratis a través de [GitHub Education][callout-student-plan-education]. El plan **Copilot Student** incluye las funciones de agente, MCP, revisión de código y Copilot CLI que utiliza este taller, así que puedes completar con él todos los recorridos.

[callout-student-plan-education]: https://github.com/education/students

> [!NOTE]
> Si usas Copilot Business o Copilot Enterprise, asegúrate de que tu administrador haya habilitado Copilot CLI.

## Primeros pasos

**[Empieza con el ejercicio 0: Requisitos previos →][ex0]**

[ex0]: 0-prerequisites/
[ex1]: 1-install-copilot-cli/
[ex2]: 2-add-star-rating/
[ex3]: 3-agent-modes/
[ex4]: 4-custom-instructions/
[ex5]: 5-agent-skills/
[ex6]: 6-mcp-playwright/
[ex7]: 7-qa-agent/
[ex8]: 8-create-pull-request/
[ex9]: 9-cli-power-tools/
[ex10]: 10-review/
[foundry]: 8-foundry-agent/
[ex9]: 9-review/
