---
title: "Lección 10 - Resumen y siguientes pasos"
description: "Repasa el flujo de trabajo de Copilot CLI, las dos solicitudes de incorporación de cambios, las personalizaciones reutilizables y otros recursos."
authors:
  - geektrainer
lastUpdated: 2026-09-29
---

Has usado GitHub Copilot CLI durante todo el flujo de trabajo de Tailspin Toys. En este proceso:

- has preparado un Codespace, instalado Copilot CLI, explorado el proyecto y localizado la incidencia de filtrado;
- has añadido las valoraciones con estrellas, revisado el resultado en un navegador reenviado y fusionado manualmente tu primera solicitud de incorporación de cambios (PR);
- has partido de la incidencia de filtrado, definido el enfoque en modo Plan, implementado la funcionalidad en modo Autopilot y revisado el resultado en modo Interactive;
- has guiado al agente con instrucciones personalizadas, personalizado la habilidad existente `quality-checks` y la has usado para ejecutar pruebas unitarias, lint y comprobaciones de tipos;
- has añadido el servidor Model Context Protocol (MCP) de Playwright y lo has usado para explorar el filtrado en un navegador real;
- has creado y seleccionado un agente personalizado de control de calidad (QA) para evaluar los requisitos, la cobertura, los resultados de la habilidad y las pruebas del navegador;
- has revisado todos los cambios del filtrado y autorizado Agent Merge para fusionar su PR;
- has explorado comandos de barra para gestionar el contexto, los modelos, las sesiones compartidas y la delegación opcional en la nube.

## Lo que has publicado

El taller incluye dos hitos de PR, cada uno en una rama creada a partir de `main` actualizado:

1. **Valoraciones con estrellas:** mostrar el valor de `starRating` existente y un estado explícito para los juegos sin valorar.
2. **Filtrado y flujo de calidad:** implementar el filtrado, actualizar las instrucciones y aplicarlas a la funcionalidad, personalizar el informe `quality-checks`, crear un perfil de QA e incluir las pruebas asociadas.

Desde la planificación del filtrado hasta la apertura de su PR, has usado la misma conversación y rama. Para simplificar el taller, hemos agrupado todo ese trabajo en una PR.

## Distintos tipos de verificación

Has comprobado el código de varias formas: con pruebas automatizadas, examinando el sitio en el navegador y pidiendo a Copilot que lo explorara mediante MCP. La habilidad `quality-checks` ha ejecutado pruebas unitarias, lint y comprobaciones de tipos, y ha incluido los resultados en el nuevo formato. El agente de QA ha reunido esos resultados con la revisión de los requisitos y la cobertura de pruebas antes de crear la PR.

Las pruebas nuevas deben cubrir carencias reales; si una ejecución de QA no requiere ninguna, puede ser correcto. Revisa el código y las pruebas antes de autorizar la fusión y actualiza las pruebas afectadas después de hacer cambios.

## Buenas prácticas

El contexto y las herramientas que proporcionas influyen en el trabajo de Copilot. En este taller has actualizado instrucciones, personalizado una habilidad, creado un perfil de QA y configurado un servidor MCP. Reutiliza estas personalizaciones entre conversaciones y adáptalas a las necesidades del equipo. Las instrucciones definen estándares; las habilidades, tareas repetibles; los agentes personalizados, perfiles especializados; y los servidores MCP conectan herramientas externas. Revisa los cambios y los resultados de las herramientas, no solo el resumen del agente.

Adapta el **modo y el modelo** a la tarea. Usa **Plan** para definir un enfoque antes de empezar, **Interactive** para seguir de cerca los cambios acotados y **Autopilot** para tareas bien delimitadas. Elige un modelo más rápido para cambios rutinarios y otro más capaz para tareas complejas.

El contexto sigue siendo tan importante como la infraestructura. Describir claramente *qué* quieres crear, *por qué* y *cómo* influye mucho en el resultado.

## Más cosas por explorar

Has completado el flujo principal. También puedes probar estas funciones de CLI:

- `/review` para pedir al agente de revisión de código que analice los cambios;
- `/rubber-duck` para explicar un problema y obtener otra perspectiva;
- `/fleet` para coordinar tareas independientes en paralelo;
- `/worktree` para aislar una tarea distinta;
- `/delegate` para enviar una tarea al agente en la nube de Copilot.

## Siguientes pasos

La mejor manera de mejorar con cualquier herramienta es seguir usándola: para código de producción, proyectos personales o esa pequeña aplicación que hace años que quieres crear. Comparte lo aprendido con el equipo y aprende de sus experiencias. Y, como siempre, explora la documentación.

Si quieres ampliar Tailspin Toys desde el terminal, continúa con la serie opcional [Foundry Backer Concierge][foundry]. Para comparar otros entornos, explora el [taller de VS Code][vscode], el [taller de la aplicación GitHub Copilot][app] o el [taller del agente en la nube de Copilot][cloud].

## Recursos

- [Acerca de GitHub Copilot CLI][about-cli]
- [Referencia de comandos de Copilot CLI][cli-reference]
- [Personalizar Copilot CLI][customize-cli]
- [Gestionar solicitudes de incorporación de cambios con Copilot CLI][manage-prs]

[previous-lesson]: ../9-cli-power-tools/
[foundry]: ../8-foundry-agent/
[vscode]: ../../vscode/
[app]: ../../app/
[cloud]: ../../cloud/
[about-cli]: https://docs.github.com/copilot/concepts/agents/about-copilot-cli
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[customize-cli]: https://docs.github.com/copilot/how-tos/copilot-cli/customize-copilot
[manage-prs]: https://docs.github.com/copilot/how-tos/copilot-cli/use-copilot-cli/manage-pull-requests
