---
title: "Ejercicio 5 - Supervisar y gestionar agentes"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← Lección anterior: Agentes personalizados][previous-lesson] |
|:--|

Cuando usas GitHub Copilot en modo agente, trabaja de forma autónoma: explora el código, propone cambios, edita archivos y ejecuta comandos. Como trabaja en tu equipo en tiempo real, Copilot Chat de VS Code muestra cada llamada a herramienta y cada edición mientras se producen. Puedes revisar las diferencias, aceptar o rechazar cambios y guiar la conversación con prompts de seguimiento sin salir del editor.

En este ejercicio:

- supervisarás en tiempo real el trabajo del agente de accesibilidad;
- revisarás y aceptarás los cambios propuestos;
- pedirás al agente durante la sesión que añada un selector de modo claro junto al de alto contraste.

## Escenario

El agente personalizado de accesibilidad del [Ejercicio 4][previous-lesson] está implementando el modo de alto contraste. Mientras trabaja, el equipo de diseño solicita también un selector de modo claro para las personas a quienes les resulta demasiado oscuro el tema predeterminado. En vez de iniciar otra conversación, guiarás la sesión existente para ampliar el trabajo.

## Supervisar el progreso de Copilot

La vista Copilot Chat muestra cada paso del agente: los archivos que explora, los comandos que ejecuta y las ediciones que propone. Cada edición aparece en línea con las diferencias y los controles **Keep** y **Undo**.

1. Vuelve a la vista Copilot Chat del Ejercicio 4.
2. Mientras trabaja el agente, desplázate por la conversación para ver las llamadas a herramientas, las lecturas y ediciones de archivos y los comandos de terminal.
3. Cuando el agente proponga una edición, verás las diferencias en línea:
   - selecciona **Keep** para aceptar el cambio;
   - selecciona **Undo** para revertirlo y pedir al agente que vuelva a intentarlo.
4. También puedes abrir el indicador **Files changed** en la parte superior de Chat para ver todos los archivos modificados durante la sesión.

> [!NOTE]
> Si una llamada a herramienta requiere permiso (por ejemplo, para ejecutar un comando de terminal), el agente se detendrá y mostrará una solicitud **Allow**. Aprueba solo los comandos que te parezcan adecuados.

5. Espera a que el agente termine de implementar el modo de alto contraste. Verás un mensaje final que resume los cambios.

## Pedir al agente que añada el modo claro

Una vez implementado el modo de alto contraste, ampliarás la misma conversación para añadir un selector de modo claro. Como continuarás en la misma sesión, el agente conservará el contexto de los componentes, los estilos y el patrón de almacenamiento local usados.

1. Envía este prompt de seguimiento desde Copilot Chat:

   ```plaintext
   Nice work! Now add a light-mode toggle alongside the high-contrast toggle. Light mode should follow the same pattern — persist via local storage and be accessible from the same area of the UI. The user should be able to enable high-contrast and light mode independently.
   ```

2. El agente explorará los cambios anteriores y propondrá los cambios necesarios para añadir el modo claro.
3. Revisa cada edición nueva con **Keep** o **Undo**, como hiciste con el modo de alto contraste.
4. Si el agente sigue un enfoque que no quieres (por ejemplo, refactoriza el selector de forma inadecuada), detenlo con el botón **Stop** junto al campo de chat y envía una aclaración.

> [!TIP]
> Guiar una sesión en curso es más rápido que empezar de nuevo. Puedes pedir ajustes («simplifica el CSS y usa variables CSS en vez de duplicar selectores»), corregir el enfoque («no añadas un tercer selector; integra el modo claro en el panel de configuración») o ampliar el alcance («añade también métodos abreviados de teclado para ambos modos»).

## Revisar los cambios

Antes de confirmar el trabajo, revisa todos los archivos modificados:

1. Abre **Source Control** en VS Code.
2. Revisa la lista completa de archivos. Deberías ver cambios en los componentes Astro, los estilos y las pruebas relacionadas.
3. Abre algunos archivos y revisa las diferencias. Confirma que se siguen las prácticas de accesibilidad del agente personalizado: atributos ARIA, navegación por teclado, HTML semántico y persistencia en el almacenamiento local.
4. Cuando estés conforme, prepara y confirma los cambios desde Source Control. Los publicarás en [la siguiente lección][next-lesson].

## Resumen y siguientes pasos

Has usado el modo agente de Copilot Chat para supervisar y guiar una sesión en curso: has revisado las ediciones, aceptado o rechazado cambios y enviado prompts de seguimiento para ampliar el trabajo sin perder el contexto.

En esta lección:

- has supervisado el trabajo de un agente en tiempo real;
- has aceptado y rechazado cambios individuales;
- has guiado la sesión con prompts de seguimiento.

En la [siguiente lección][next-lesson] publicarás el trabajo de accesibilidad en una solicitud de incorporación de cambios y revisarás los cambios generados durante el laboratorio.

## Recursos

- [Copilot Chat en VS Code][copilot-chat-vscode]
- [Usar el modo agente][agent-mode]

---

| [← Lección anterior: Agentes personalizados][previous-lesson] | [Siguiente lección: Iterar sobre el trabajo de Copilot →][next-lesson] |
|:--|--:|

[previous-lesson]: ../4-custom-agents/
[next-lesson]: ../6-iterating/
[copilot-chat-vscode]: https://code.visualstudio.com/docs/copilot/chat/copilot-chat
[agent-mode]: https://code.visualstudio.com/docs/copilot/chat/chat-agent-mode
