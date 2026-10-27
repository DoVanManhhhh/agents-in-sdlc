---
title: "Ejercicio 2 - Agente en la nube de GitHub Copilot"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← Lección anterior: Instrucciones personalizadas][previous-lesson] |
|:--|

Muchas organizaciones tienen deuda técnica: problemas de seguridad sin resolver, código heredado que necesita actualizarse o funcionalidades que siguen en el backlog por falta de tiempo. El agente en la nube de GitHub Copilot puede actualizar código y añadir funcionalidades de forma autónoma. Al terminar, crea una PR en borrador para que la revise un desarrollador. Así puedes delegar tareas tediosas, acelerar el desarrollo y centrarte en problemas de mayor alcance.

En este ejercicio explorarás cómo:

- personalizar el entorno de generación de código;
- garantizar que las operaciones se realicen de forma segura;
- definir incidencias con un alcance claro;
- asignar incidencias a Copilot.

## Escenarios

Tailspin Toys tiene deuda técnica. Los contratistas que crearon la primera versión del sitio dejaron la documentación en mal estado: de hecho, no hay documentación. El primer paso será añadir comentarios TSDoc a todas las funciones exportadas.

Además, el equipo de diseño quiere mejorar el descubrimiento de juegos. Quiere mostrar juegos relacionados (otros títulos de la misma categoría) en la página de detalles. No hace falta una implementación pulida; solo una versión para probar la experiencia. La tarea bloquea el trabajo actual, pero hay incidencias de mayor prioridad.

Son tareas que suelen aplazarse y que se pueden asignar al agente en la nube. Este trabaja de forma asíncrona mientras tú te ocupas de otras tareas; después puedes revisar el resultado.

## Introducción al agente en la nube de GitHub Copilot

El [agente en la nube de GitHub Copilot](https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent#overview-of-copilot-cloud-agent-formerly-copilot-coding-agent) puede trabajar en segundo plano de forma parecida a un desarrollador. Por ejemplo, puedes [asignarle una incidencia de GitHub](https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions). Copilot crea una PR en borrador para mostrar el progreso, configura un entorno y empieza a trabajar. Puedes inspeccionar la sesión mientras se ejecuta o después de terminar. Cuando la solución esté lista para revisarse, Copilot te mencionará en la PR.

## La importancia de acotar bien las instrucciones

GitHub Copilot no es magia: sigue siendo necesario pensar. Incluso las tareas aparentemente sencillas pueden ser complejas. [Define cuidadosamente el alcance de las tareas][cloud-agent-best-practices] y trata al agente como a un compañero de programación con IA: trabaja por etapas, aprende, experimenta e itera. Los fundamentos del desarrollo de software no cambian al añadir IA generativa.

## Instrucciones personalizadas del repositorio

En ejercicios anteriores has aprendido cómo guían a Copilot las instrucciones personalizadas. Antes de asignar una tarea al agente, revisa los archivos de instrucciones existentes para observar después su efecto. Ábrelos en github.com o en un codespace:

- `.github/copilot-instructions.md`: revisa **Code standards**, en especial las convenciones de TypeScript y los comentarios TSDoc.
- `.github/instructions/unit-tests.instructions.md`: observa el frontmatter `applyTo`, que aplica estas instrucciones a los archivos `**/*.test.ts`.

Cuando asignes la incidencia `Code lacks documentation`, revisa si la PR incluye comentarios TSDoc, convenciones de TypeScript y encabezados de comentario.

## Configurar el entorno de desarrollo del agente

El agente usa [GitHub Actions][github-actions] como entorno de trabajo. Puedes personalizarlo mediante el flujo de configuración `.github/workflows/copilot-setup-steps.yml`, que se ejecuta antes de que el agente empiece. Este archivo ya está configurado para instalar Node.js y dependencias, los navegadores de pruebas y la base de datos SQLite migrada y precargada de la aplicación Astro:

```yaml
name: "Copilot Setup Steps"

# Permite probar los pasos de configuración desde la pestaña "Actions" del repositorio
on: workflow_dispatch

env:
  ASTRO_TELEMETRY_DISABLED: "1"

jobs:
  copilot-setup-steps:
    runs-on: ubuntu-latest
    # Define los permisos mínimos necesarios para *tus pasos*. Copilot recibirá su propio token para las operaciones.
    permissions:
      # Si quieres clonar el repositorio como parte de la configuración (por ejemplo, para instalar dependencias), necesitarás el permiso `contents: read`. Si no lo clonas aquí, Copilot lo hará automáticamente al terminar estos pasos.
      contents: read
    steps:
      - name: Checkout code
        uses: actions/checkout@v5

      # Configuración de frontend y aplicación - Node.js (la aplicación usa Astro + Drizzle/libSQL)
      - name: Set up Node.js
        uses: actions/setup-node@v6
        with:
          node-version: "lts/*"
          cache: "npm"
          cache-dependency-path: "./package-lock.json"

      - name: Install JavaScript dependencies
        run: npm ci

      - name: Install Playwright browsers
        run: npx playwright install --with-deps chromium

      # Migra y precarga la base de datos SQLite local para que las compilaciones y pruebas tengan datos.
      - name: Set up the database
        run: npm run db:setup
```

El archivo se parece a cualquier flujo de trabajo de GitHub, pero tiene algunos aspectos importantes:

- Incluye un único trabajo llamado `copilot-setup-steps`, que se ejecuta en GitHub Actions antes de que Copilot empiece a trabajar en la PR.
- El desencadenador `workflow_dispatch` permite ejecutar manualmente el flujo desde la pestaña **Actions** para comprobar que funciona.

## Añadir documentación

La falta de documentación o la información desactualizada dificultan el mantenimiento y la incorporación de nuevos desarrolladores. Copilot puede ayudar a crear documentación; así que le asignarás esta tarea y revisarás su resultado en un ejercicio posterior.

1. Abre tu repositorio en github.com en una pestaña nueva.
2. Selecciona **Issues** y, después, **New issue**.
3. Selecciona **Blank issue**.
4. Escribe `Code lacks documentation` en **Title**.
5. En **Description**, escribe:

   ```plaintext
   Our organization has a requirement that functions and methods include TSDoc doc comments where helpful. Unfortunately, recent updates haven't followed this standard. We need to update the existing code to ensure doc comments are included where they clarify behavior.
   ```

6. Selecciona **Create**. En el lado derecho, selecciona **Assign to Copilot** y, después, **Assign**.

   ![Asignar una incidencia a Copilot](../../../_images/shared-assign-copilot.png)

   ![Detalles de la asignación a Copilot](../../../_images/ex4-assign-copilot-details.png)

7. Abre **Pull Requests** y selecciona la PR nueva, cuyo título será parecido a `[WIP]: Code lacks documentation`. Si todavía no aparece, espera un momento y actualiza el navegador.
8. Al cabo de unos minutos, Copilot habrá creado una lista de tareas. Puede tardar porque está creando el entorno (ejecuta el flujo anterior), analizando el proyecto y eligiendo un enfoque.
9. Revisa las tareas. Desplázate por la cronología de la PR para ver cuándo empieza Copilot.
10. Selecciona **View session**.

   ![Vista de la sesión de Copilot](../../../_images/ex4-view-session.png)

> [!CAUTION]
> Puede que tengas que actualizar el navegador para ver el indicador actualizado.

11. Explora la sesión en directo: verás cómo Copilot explora el código y su estado, planifica y crea código.

El proceso puede tardar varios minutos. El agente en la nube trabaja de forma asíncrona, así que ahora le asignarás otra tarea mientras tú sigues con el taller.

## Añadir una sección de juegos relacionados

Puedes dividir el trabajo: Copilot se ocupará de una tarea mientras tú haces otra. Asigna al agente la sección de juegos relacionados:

1. Vuelve al repositorio en github.com y selecciona **Issues** → **New issue** → **Blank issue**.
2. Escribe `Show related games on the game details page` en **Title**.
3. En **Description**, escribe:

   ```markdown
   We want to help people discover more games by showing related games on each game's details page. The design team wants to explore the UX and do some acceptance testing. Our requirements are:

   - Add a data-access helper in `src/lib/` that returns other games in the same category as a given game, excluding that game
   - Show a "Related games" section on the game details page that uses the helper
   - Handle the case where a game has no related games
   - There should be unit tests created for the new helper
   - Before creating the PR, ensure all tests pass
   ```

4. Selecciona **Create**. En el lado derecho, selecciona **Assign to Copilot** y, después, **Assign**.

   ![Asignar una incidencia a Copilot](../../../_images/shared-assign-copilot.png)

Al poco tiempo verás 👀 en el primer comentario de la incidencia para indicar que Copilot ya está trabajando.

![Copilot usa el emoji de ojos para indicar que trabaja en la incidencia](../../../_images/ex4-issue-eyes-emoji.png)

El agente trabaja como un desarrollador de software y no necesita que lo supervises continuamente. Revisa el resultado cuando termine. Ahora explorarás cómo crear y usar agentes personalizados.

## Resumen y siguientes pasos

Has explorado el [agente en la nube de GitHub Copilot][copilot-agents]. Puedes asignarle incidencias para abordar deuda técnica, crear funcionalidades o migrar código entre frameworks. En este ejercicio:

- has personalizado el entorno de generación de código;
- has aprendido a realizar las operaciones de forma segura;
- has aprendido por qué conviene definir incidencias con un alcance claro;
- has asignado incidencias a Copilot.

Mientras Copilot trabaja, puedes [crear y usar agentes personalizados][next-lesson]. El agente en la nube también puede usar [servidores MCP][cloud-agent-mcp] e instrucciones personalizadas.

## Recursos

- [Acerca del agente en la nube de Copilot][copilot-agents]
- [Asignar incidencias de GitHub a Copilot][assign-issue]
- [Buenas prácticas para el flujo de configuración del agente en la nube][cloud-agent-best-practices]

| [Siguiente lección: Agentes personalizados →][next-lesson] |
|--:|

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-custom-agents/
[cloud-agent-mcp]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/extend-cloud-agent-with-mcp
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[github-actions]: https://docs.github.com/actions
