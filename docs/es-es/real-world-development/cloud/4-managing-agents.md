---
title: "Ejercicio 4 - Supervisar y gestionar agentes"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

En los dos ejercicios anteriores has pedido al agente en la nube que realice tres tareas para mejorar la experiencia y añadir funcionalidades. Aunque trabaja de forma autónoma y asíncrona, es importante supervisar las tareas.

Hay varias herramientas para gestionar las tareas asignadas, como la [página de agentes][agents-page] de GitHub.com. Desde este centro puedes ver las tareas con PR abiertas, explorar las operaciones realizadas y guiar las sesiones en curso.

En este ejercicio:

- explorarás la página de agentes para supervisar las tareas del agente en la nube;
- guiarás una sesión en curso para pedir otra funcionalidad.

## Escenario

Después de pedir al agente el modo de alto contraste, el equipo decide añadir también un modo claro. Como ya se están actualizando los estilos y se está añadiendo un selector, pedirás al agente que incluya ambas funciones.

## Revisar las tareas del agente

Comprueba el estado de las tareas asignadas:

1. Abre la [página de agentes de Copilot](https://github.com/copilot/agents).
2. Revisa las tareas del panel principal y del panel izquierdo. Deberías encontrar las incidencias de documentación, las API para modificar juegos y el modo de alto contraste.
3. Selecciona una tarea en curso y revisa las operaciones realizadas, como obtener el código del repositorio, crear el entorno, configurar servidores MCP y completar la tarea.

> [!NOTE]
> Los pasos exactos varían según el estado del trabajo de Copilot y el enfoque utilizado.

4. Observa también el panel de PR de la derecha, donde puedes revisar la solicitud y los archivos modificados.

## Guiar al agente en la nube

Pide a Copilot que añada el modo claro mientras implementa el modo de alto contraste:

1. Selecciona la sesión relacionada con el modo de alto contraste. El título puede variar.

   ![Sesión de accesibilidad en mission control](../../../_images/ex6-accessibility-session.png)

2. Espera unos minutos hasta que termine la configuración y empiece el trabajo.
3. En el cuadro **Steer active session while Copilot is working**, escribe este prompt:

   ```plaintext
   While we are working on a high contrast mode, let's also add a light mode. There should be a switch for this mode as well where users can select their desired display mode.
   ```

   ![Tarea del agente en la nube con el cuadro para guiar la sesión activa resaltado](../../../_images/ex6-steer-cloud-agent-task.png)

4. Pulsa <kbd>Enter</kbd> para enviar el prompt.
5. Observa cómo Copilot lo confirma y lo incorpora al flujo de trabajo.

## Dejar que Copilot trabaje

Copilot incorporará la nueva solicitud cuando termine el paso que estaba ejecutando. El proceso puede tardar varios minutos; puedes aprovechar ese tiempo para repasar lo aprendido.

## Resumen y siguientes pasos

Has explorado la página de agentes de Copilot, el centro para supervisar y guiar las tareas del agente en la nube. Puedes seguir las tareas activas y completadas, revisar el trabajo y redirigir una sesión para ajustar su alcance. En este ejercicio:

- has usado mission control y la página de agentes para supervisar tareas;
- has redirigido una sesión para pedir otra funcionalidad.

Mientras Copilot termina las funciones de accesibilidad, [revisarás e iterarás sobre sus solicitudes de incorporación de cambios][next-lesson].

## Recursos

- [Página de agentes de Copilot][agents-page]
- [Acerca de los agentes personalizados][custom-agents]

---

| [← Lección anterior: Agentes personalizados][previous-lesson] | [Siguiente lección: Iterar sobre el trabajo de Copilot →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-custom-agents/
[next-lesson]: ../5-iterating/
[agents-page]: https://github.blog/changelog/2025-07-03-agents-page-for-copilot-coding-agent-in-public-preview
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
