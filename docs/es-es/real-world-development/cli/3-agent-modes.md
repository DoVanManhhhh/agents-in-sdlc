---
title: "Lección 3 - Modos de agente: Plan y Autopilot"
description: "Usa Plan para acordar un enfoque, Autopilot para crear el filtrado a partir de una incidencia e Interactive para revisar el resultado."
authors:
  - geektrainer
lastUpdated: 2026-09-18
---

Empezamos añadiendo una pequeña funcionalidad al proyecto, pero los cambios más amplios necesitan un proceso más completo. GitHub Copilot CLI está diseñado para trabajar con el flujo de tu organización y ayudarte a crear las soluciones adecuadas de la forma apropiada. En esta y las siguientes lecciones seguirás un proceso habitual de desarrollo con agentes: partirás de una incidencia para crear una funcionalidad, comprobarás el código, validarás el comportamiento y, finalmente, la fusionarás en el proyecto.

> [!NOTE]
> Seguirás con la misma conversación y rama durante todo el flujo de la funcionalidad. Normalmente usarías distintas ramas o PR para los diferentes tipos de archivos, pero aquí simplificaremos el proceso para centrarnos en los conceptos principales.

En esta lección:

- iniciarás una conversación de Copilot a partir de una incidencia de GitHub;
- definirás los requisitos en el modo Plan;
- implementarás la funcionalidad con el modo Autopilot;
- revisarás el código;
- validarás la funcionalidad manualmente en un navegador reenviado.

En las siguientes lecciones actualizarás las instrucciones del repositorio, personalizarás la habilidad existente `quality-checks`, añadirás validación MCP, crearás un agente de QA y abrirás la PR de la funcionalidad.

## Escenario

El catálogo de Tailspin Toys crece y los visitantes necesitan filtrar los juegos por categoría y editorial. La incidencia del backlog describe la funcionalidad, pero es necesario acordar algunos detalles, como la combinación de categorías, antes de escribir código. Usarás el modo Plan para resolver estas decisiones y, después, autorizarás una implementación acotada con Autopilot.

## Contexto

Incorporar agentes de programación con IA al flujo de desarrollo no cambia sus fundamentos. De hecho, los hace aún más importantes. La mayoría de los desarrolladores siguen un proceso parecido a este:

1. Partir de una incidencia registrada que describa el trabajo.
2. Crear un plan de implementación.
3. Crear y revisar el código.
4. Ejecutar pruebas para validar el código.
5. Validar manualmente la nueva funcionalidad.
6. Crear una solicitud de incorporación de cambios (PR).
7. Tras la revisión del código y el éxito de la integración continua, fusionar el cambio.

> [!NOTE]
> Los detalles concretos dependen del equipo y de la organización, pero la mayoría de los procesos son variantes de este patrón.

Seguir este enfoque habitual garantiza que el código generado por IA cumpla los requisitos establecidos y pase por el mismo proceso de revisión que el código escrito manualmente.

## Modos de conversación

El **modo de conversación** determina el grado de autonomía del agente. Pulsa <kbd>Shift</kbd>+<kbd>Tab</kbd> para cambiar de modo:

- **Interactive**: trabajas con el agente. Este propone cambios y espera tus indicaciones antes de continuar.
- **Plan**: el agente crea primero un plan y no puede editar archivos del proyecto.
- **Autopilot**: el agente trabaja de forma autónoma: escribe código, ejecuta pruebas e itera hasta completar la tarea.

Empieza en el modo Plan, revisa el plan y, después, usa Autopilot para implementarlo.

## Empezar desde la incidencia

Antes de comenzar a trabajar en el filtrado, vuelve a tu Codespace y comprueba que el repositorio y el terminal estén listos.

1. Vuelve a tu Codespace. Si está detenido, reinícialo.
2. Confirma que la PR de las valoraciones con estrellas se ha fusionado.
3. Si el terminal no está abierto, pulsa <kbd>Control</kbd>+<kbd>\`</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>\`</kbd> (Windows/Linux).
4. Actualiza `main` y crea una rama para el filtrado:

   ```bash
   git checkout main
   git pull --ff-only
   git checkout -b game-filters-cli
   ```

5. Inicia Copilot CLI:

   ```bash
   copilot --yolo
   ```

6. Pulsa <kbd>Tab</kbd> dos veces para abrir la pestaña **Issues**.
7. Pulsa <kbd>A</kbd> para mostrar todas las incidencias.
8. Usa las teclas de dirección para resaltar la incidencia **Allow users to filter games by category and publisher**.
9. Pulsa <kbd>C</kbd> para añadir la incidencia al prompt y volver a la pestaña **Session**.

Observa que el prompt ahora empieza por `#7` (o por un número parecido). El carácter `#` permite incluir en el contexto de GitHub una incidencia o solicitud de incorporación de cambios.

## Planificar la funcionalidad de filtrado

La planificación te permite acordar un enfoque antes de pedir a Copilot que implemente una funcionalidad o realice una tarea. Es recomendable dedicar algo de tiempo a planificar las tareas complejas. Cambia al modo Plan y pide a Copilot que cree el plan:

1. Pulsa <kbd>Shift</kbd>+<kbd>Tab</kbd> para cambiar al modo Plan. Confirma que el indicador debajo del prompt muestra **Plan**.
2. Después de la referencia a la incidencia que añadiste en el paso anterior, introduce este prompt:

   ```plaintext
   Create a plan for implementing this feature.
   ```

Copilot explora el proyecto y determina el mejor enfoque para elaborar el plan.

3. Puede que Copilot te pregunte cómo debería funcionar el filtrado. Responde según tus preferencias; no hay una única respuesta correcta.
4. Cuando el plan esté listo, pulsa <kbd>Control</kbd>+<kbd>E</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>E</kbd> (Windows/Linux) para ampliarlo.
5. Desplázate por el plan y revísalo.
6. Pide a Copilot que modifique cualquier parte que no refleje tus decisiones.

## Aprobar Autopilot

Una vez escrito y revisado el plan, toca implementarlo con Autopilot. Este modo permite a Copilot iterar sobre el problema hasta considerar que está resuelto.

1. Selecciona **Accept plan and build on autopilot (recommended)** o una opción con un nombre parecido en tu versión.
2. Confirma que el indicador bajo el prompt muestra **Autopilot**.
3. Observa cómo Copilot sigue el plan acordado, genera código y ejecuta pruebas.

> [!NOTE]
> Al aprobarlo, la implementación puede empezar de inmediato, así que revisa primero el plan. Si Copilot indica que faltan dependencias o que hay un conflicto de puertos, resuelve el problema de configuración antes de dar las comprobaciones por terminadas.

## Revisar y verificar la implementación

Como cualquier otro código, el código generado debe revisarse antes de fusionarlo. Revisa el código y ejecuta el sitio para comprobar que todo funciona:

1. Pulsa <kbd>Shift</kbd>+<kbd>Tab</kbd> para volver al modo Interactive. Confirma que el indicador no muestra **Plan** ni **Autopilot**.
2. Escribe `/diff` e inspecciona la implementación del filtrado y las pruebas.
3. Compara el resultado con la incidencia y las decisiones de planificación.
4. Cuando hayas revisado el código, pulsa <kbd>Esc</kbd> para salir de la vista de diferencias.
5. Revisa los resultados de las comprobaciones del proyecto y pide a Copilot que resuelva los errores.

## Explorar la nueva funcionalidad

El código parece correcto, pero ¿se ejecuta? Inicia la aplicación como antes y abre el sitio a través del puerto reenviado de Codespaces.

1. Pide a Copilot que inicie la aplicación:

   ```plaintext
   Start the app so I can try the filtering feature in my browser. Tell me the URL and leave the server running.
   ```

2. Cuando Codespaces indique que el puerto `4321` está disponible, selecciona **Open in Browser**.
3. Prueba los filtros de categoría y editorial, así como las combinaciones acordadas en el plan.
4. Confirma que el comportamiento al restablecer los filtros y cuando no hay resultados coincide con la incidencia y tus decisiones.
5. Vuelve a tu Codespace y pide a Copilot que detenga el servidor de desarrollo que ha iniciado.

## Resumen y siguientes pasos

Has usado distintos modos de conversación para crear y revisar una funcionalidad. En esta lección:

- has iniciado una conversación de Copilot a partir de una incidencia de GitHub;
- has definido los requisitos en el modo Plan;
- has implementado la funcionalidad con Autopilot;
- has revisado el código;
- has validado la funcionalidad manualmente en un navegador reenviado.

A continuación, profundizarás en cómo se genera el código y cómo seguir las prácticas documentadas mediante [instrucciones personalizadas][next-lesson].

## Recursos

- [Autopilot en GitHub Copilot CLI][autopilot]
- [Referencia de comandos de Copilot CLI][cli-reference]

[autopilot]: https://docs.github.com/copilot/concepts/agents/copilot-cli/autopilot
[cli-reference]: https://docs.github.com/copilot/reference/copilot-cli-reference/cli-command-reference
[previous-lesson]: ../2-add-star-rating/
[next-lesson]: ../4-custom-instructions/
