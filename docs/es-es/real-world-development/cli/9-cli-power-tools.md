---
title: "Lección 9 - Comandos de barra de GitHub Copilot CLI"
description: "Explora los comandos de barra para gestionar el contexto, seleccionar modelos, compartir sesiones y delegar tareas opcionalmente en la nube."
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

Como cualquier herramienta de CLI, GitHub Copilot CLI incluye muchos comandos de barra. Estos permiten acceder a funciones avanzadas, consultar información interna y cambiar la configuración. Ya has usado comandos como `/diff`, `/mcp`, `/skills`, `/agent` y `/pr`. Ahora explorarás algunos más.

En esta lección:

- usarás `/context` y `/compact` para explorar cómo gestiona Copilot el contexto de la conversación;
- usarás `/model` para explorar los modelos disponibles;
- aprenderás a exportar o compartir una sesión con `/share`;
- explorarás comandos opcionales para trabajar en paralelo, usar worktrees y delegar tareas en el agente en la nube.

## Escenario

Ya has terminado el flujo principal de CLI. Ahora descubrirás algunas funciones adicionales: gestionar el contexto, cambiar de modelo, compartir sesiones y, de forma opcional, delegar trabajo al [agente en la nube de Copilot][about-cloud-agent].

## Explorar el contexto de Copilot CLI

En tareas grandes o complejas puedes llegar al límite de contexto del modelo. Copilot CLI compacta automáticamente la conversación cuando hace falta, pero también puedes inspeccionar o compactar el contexto con comandos de barra.

1. Vuelve a tu Codespace e inicia Copilot CLI desde la raíz del repositorio si todavía no está abierto.
2. Escribe:

   ```plaintext
   /context
   ```

3. Observa el modelo, el uso actual de tokens y la distribución del contexto entre instrucciones del sistema, herramientas, mensajes y espacio libre.
4. Compacta la conversación:

   ```plaintext
   /compact
   ```

5. Vuelve a ejecutar `/context` y compara el resultado. Si la conversación ya es corta, puede que no haya cambiado mucho.

> [!NOTE]
> Copilot CLI compacta el contexto automáticamente a medida que se llena la ventana. Usa `/compact` para elegir cuándo hacerlo. Usa `/clear` o `/new` si vas a empezar una tarea distinta y quieres una conversación nueva.

## Elegir un modelo

Los modelos tienen capacidades distintas y cada persona tiene sus propias preferencias. Copilot CLI permite mostrar los modelos y seleccionar el que quieras usar.

1. Escribe:

   ```plaintext
   /model
   ```

2. Explora los modelos disponibles y la información de uso.
3. Mantén el modelo actual, selecciona otro o pulsa <kbd>Esc</kbd> para cerrar la lista.

## Compartir una sesión

Colaborar y compartir lo aprendido ayuda a todo el equipo a aprovechar mejor las herramientas de IA. El comando `/share` puede exportar una sesión a un archivo Markdown o HTML, crear un vínculo para compartirla o publicar un gist de GitHub.

1. Escribe `/help` y consulta las opciones de `/share` disponibles en tu versión.
2. Si quieres compartir la sesión, elige el destino adecuado; por ejemplo, `/share file` para exportar un archivo Markdown local.
3. Revisa el contenido exportado antes de enviarlo o publicarlo. Las exportaciones pueden incluir prompts, respuestas y detalles del proyecto.

Publicar un vínculo o gist es opcional. No publiques contenido del repositorio o de la conversación que el equipo no quiera compartir.

## Opcional: ampliar o delegar el trabajo

El taller principal ya ha terminado. Copilot CLI también ofrece comandos para tareas más grandes:

- `/fleet` puede dividir tareas independientes entre subagentes y ejecutarlas en paralelo.
- `/worktree` puede crear un worktree de Git aislado para una tarea distinta.
- `/delegate` puede enviar una tarea al agente en la nube de Copilot, que trabaja de forma asíncrona y puede abrir una solicitud de incorporación de cambios.

Estos comandos son opcionales porque pueden crear worktrees adicionales o trabajo remoto. Antes de probarlos, inicia una tarea nueva y bien definida. Para profundizar en el trabajo asíncrono con agentes, continúa con el [taller del agente en la nube][cloud-workshop].

## Resumen y siguientes pasos

Los comandos de barra de Copilot CLI te permiten configurar la herramienta, compartir sesiones y consultar su funcionamiento. En esta lección:

- has usado `/context` y `/compact` para explorar la gestión del contexto;
- has usado `/model` para explorar los modelos disponibles;
- has aprendido cómo exportar o compartir una sesión con `/share`;
- has explorado comandos opcionales para trabajar en paralelo, usar worktrees y delegar tareas en el agente en la nube.

Copilot CLI incluye muchos otros comandos de barra. Para cerrar el recorrido, [repasarás lo aprendido][next-lesson] y descubrirás los siguientes pasos.

## Recursos

- [Referencia de comandos de Copilot CLI][cli-reference]
- [Gestión del contexto en Copilot CLI][context-management]
- [Acerca del agente en la nube de Copilot][about-cloud-agent]

[previous-lesson]: ../8-create-pull-request/
[next-lesson]: ../10-review/
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[context-management]: https://docs.github.com/copilot/concepts/agents/copilot-cli/context-management
[about-cloud-agent]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-workshop]: ../../cloud/
