---
title: "Lección 8 - Crear y fusionar la PR de la funcionalidad"
description: "Revisa el filtrado, las instrucciones, la habilidad actualizada, el perfil de QA y las pruebas; después crea una PR y usa Agent Merge."
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

La implementación del filtrado, las actualizaciones de instrucciones y de la habilidad, el perfil de control de calidad (QA) y las pruebas están guardados en una rama. Ahora toca revisarlos en conjunto y abrir una solicitud de incorporación de cambios. Fusionaste manualmente la PR de las valoraciones con estrellas; esta vez dejarás que **Agent Merge** gestione el proceso.

> [!NOTE]
> Lo normal sería separar la funcionalidad, las instrucciones, la actualización de la habilidad y el agente de QA en varias PR. Para simplificar el taller, has mantenido todo el trabajo de filtrado y del flujo de calidad en una conversación y una rama.

En esta lección:

- aprenderás qué es Agent Merge y cómo automatiza el ciclo de vida de una PR;
- inspeccionarás todos los cambios de la funcionalidad y las pruebas de verificación;
- crearás la PR del filtrado;
- activarás Agent Merge solo después de revisar los cambios y confirmarás que la PR se ha fusionado.

## Escenario

Durante el flujo de trabajo de filtrado, has usado Copilot para planificar, implementar y verificar una funcionalidad. Tailspin Toys quiere automatizar el trabajo restante de la PR, pero mantener bajo el control del desarrollador la autorización para fusionarla.

## Introducción a Agent Merge

**Agent Merge** automatiza el trabajo restante para incorporar una solicitud de incorporación de cambios. Cuando lo activas, Copilot resuelve los bloqueos de la PR (por ejemplo, corrige errores de integración continua [CI], responde a comentarios de revisión y vuelve a aplicar la base) y, si el repositorio lo permite, activa la fusión automática de GitHub.

Hasta ahora seleccionabas **Merge pull request** manualmente. Agent Merge puede encargarse de ese proceso. Revisa el trabajo y confirma que está listo antes de activarlo.

## Usar Agent Merge para gestionar la PR

Con todo el código creado, revísalo, crea la PR y deja que Agent Merge se encargue del resto.

1. Vuelve a tu Codespace.
2. Escribe `/agent` para abrir el cuadro de diálogo de agentes.
3. Selecciona **Default** en la lista y pulsa <kbd>Enter</kbd>.
4. Crea una PR con el comando `/pr create`.
5. Activa Agent Merge con `/pr agentmerge`.
6. Copilot seguirá el proceso de integración continua de la PR. Cuando todo termine correctamente, realizará la fusión.
7. Confirma que Copilot muestra un mensaje parecido a «PR #14 was squash-merged successfully».

> [!IMPORTANT]
> Agent Merge no omite las aprobaciones obligatorias, la protección de ramas, las colas de fusión, la configuración del repositorio ni los permisos que falten. Si se bloquea, revisa el motivo indicado y completa manualmente la fusión revisada cuando el repositorio lo permita.

## Resumen y siguientes pasos

Has automatizado varios pasos del desarrollo: la generación de código, las pruebas y la validación y, ahora, el proceso de la solicitud de incorporación de cambios. En esta lección:

- has aprendido qué es Agent Merge y cómo automatiza el ciclo de vida de una PR;
- has inspeccionado todos los cambios de la funcionalidad y las pruebas de verificación;
- has creado la PR del filtrado;
- has activado Agent Merge después de revisar los cambios y has confirmado la fusión.

A continuación, [explorarás otros comandos de barra de Copilot CLI][next-lesson] para gestionar el contexto y los modelos, compartir sesiones y, de forma opcional, delegar trabajo en la nube.

## Recursos

- [Gestionar solicitudes de incorporación de cambios con Copilot CLI][manage-prs]
- [Referencia de comandos de Copilot CLI][cli-reference]

[previous-lesson]: ../7-qa-agent/
[next-lesson]: ../9-cli-power-tools/
[manage-prs]: https://docs.github.com/copilot/how-tos/copilot-cli/use-copilot-cli/manage-pull-requests
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
