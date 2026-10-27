---
title: "Ejercicio 5: Iterar sobre el trabajo de GitHub Copilot"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

| [← Lección anterior: Gestionar agentes][previous-lesson] |
|:--|

## Revisar el trabajo

Durante el laboratorio has pedido a GitHub Copilot que documente el código, añada juegos relacionados y mejore la accesibilidad con selectores de alto contraste y modo claro. Ahora revisarás los cambios y, si hace falta, pedirás mejoras.

### Escenario

Los fundamentos del diseño de software y DevOps no cambian al incorporar IA generativa. Hay que revisar el código generado y seguir el proceso habitual. Revisarás las sugerencias de Copilot para la documentación, los juegos relacionados y la accesibilidad antes de habilitar la revisión del equipo.

## Seguridad y agente en la nube de GitHub Copilot

El agente trabaja de forma asíncrona y sin supervisión, por lo que hay límites de seguridad:

- Copilot solo tiene acceso de lectura al repositorio y acceso de escritura **únicamente** a la rama que usa para sus cambios.
- El agente se ejecuta en GitHub Actions, dentro de un entorno separado y efímero.
- Una persona debe aprobar los flujos de trabajo de GitHub Actions antes de ejecutarlos.
- De forma predeterminada, el acceso a recursos externos, incluidos los servidores MCP, está limitado.

## Revisar la documentación generada

Empieza por la primera solicitud de incorporación de cambios (PR), que añade documentación al código mediante la interfaz habitual de GitHub.com.

> [!NOTE]
> Puede que la PR indique que un firewall bloquea a Copilot. Es lo esperado: el acceso a recursos externos, incluidos los servidores MCP, está limitado de forma predeterminada. Si quieres, puedes [configurar o deshabilitar el firewall][agent-firewall].

1. Abre tu repositorio en github.com y selecciona **Pull Requests**.
2. Abre la PR titulada, por ejemplo, **Add missing documentation**. Si aún está en curso y muestra **[WIP]**, espera unos minutos.
3. Selecciona **Files changed** y revisa los cambios.

   ![Pestaña Files changed](../../../_images/shared-pr-files-changed.png)

4. Busca los comentarios TSDoc, las convenciones de TypeScript y los encabezados de comentario. Proceden de los archivos de instrucciones que revisaste al principio del Ejercicio 2.
5. Vuelve a **Conversation**. Si hay flujos de trabajo pendientes, selecciona **Approve and run workflows**.

   ![Aprobar y ejecutar flujos de trabajo](../../../_images/shared-approve-workflows.png)

6. Espera a que se ejecuten las comprobaciones del proyecto para la aplicación Astro. Puede tardar varios minutos.

> [!NOTE]
> Mientras revisas la PR, puede aparecer una advertencia de que el firewall bloquea a Copilot. Es normal debido al acceso limitado a recursos externos.

### Pedir cambios a GitHub Copilot

Puedes mencionar a Copilot en comentarios de la PR o en comentarios en línea del código. Copilot los verá e iniciará otra sesión para resolverlos. Los resultados son probabilísticos, así que no hay un prompt único. Puedes pedir, por ejemplo:

- añadir encabezados de comentario que describan cada archivo;
- añadir comentarios TSDoc a archivos TypeScript y Astro;
- crear un README con una descripción de la estructura de la aplicación Astro.

1. Añade un comentario que solicite un cambio y menciona a **@copilot**.
2. Selecciona **View Session** para seguir el trabajo. Copilot iniciará otra sesión para aplicar el cambio.
3. Usa **Back to pull request** para volver a la PR.

   ![Volver a la solicitud de incorporación de cambios](../../../_images/ex7-back-to-pr.png)

4. Cuando Copilot termine, verás un commit nuevo en la PR. Revisa sus cambios en **Files changed**.

Puedes seguir iterando hasta que estés conforme. Después, marca la PR como lista para revisión y fusiónala.

![Marcar la PR como lista para revisión](../../../_images/ex7-ready-for-review.png)

## Revisar la funcionalidad de juegos relacionados

Revisa la PR de Copilot para la incidencia sobre los juegos relacionados:

1. Abre **Pull Requests** en tu repositorio.
2. Selecciona la PR titulada, por ejemplo, **Show related games on the game details page**.
3. Revisa el código en **Files changed**.
4. Vuelve a **Conversation**. Si hay flujos de trabajo pendientes, selecciona **Approve and run workflows** y espera a que terminen las comprobaciones de la aplicación Astro.
5. **Opcional:** prueba manualmente la funcionalidad desde el codespace. Sustituye `<branch-name>` por la rama creada por Copilot, por ejemplo, `copilot/fix-8`:

   ```bash
   git fetch origin
   git checkout <branch-name>
   ```

Copilot ha creado la funcionalidad de juegos relacionados. Puedes pedirle cambios mediante un comentario en **Conversation**, como ajustar la cantidad de juegos o añadir encabezados y comentarios TSDoc. Recuerda que esta tarea se asignó antes de actualizar las instrucciones personalizadas.

## Revisar las funciones de accesibilidad

Por último, revisa la PR del agente personalizado de accesibilidad. Debe incluir el modo de alto contraste que asignaste en el Ejercicio 3 y el modo claro solicitado en mission control en el Ejercicio 4.

1. Abre **Pull Requests** en tu repositorio y selecciona la PR titulada, por ejemplo, **Add high contrast mode to website**. Si todavía aparece como **[WIP]**, espera a que termine el agente.
2. Revisa el código en **Files changed**, en especial:
   - los selectores de la interfaz para cambiar de modo;
   - el almacenamiento local de las preferencias;
   - los cambios de CSS para los modos de alto contraste y claro;
   - los atributos de accesibilidad, como las etiquetas ARIA y la navegación por teclado;
   - el código JavaScript/TypeScript que gestiona los modos.
3. Vuelve a **Conversation**. Si hay flujos de trabajo pendientes, selecciona **Approve and run workflows** y espera a que terminen las comprobaciones.
4. **Opcional:** para probar manualmente las funciones, cambia al codespace y ejecuta estos comandos (sustituye `<branch-name>` por la rama de Copilot):

   ```bash
   git fetch origin
   git checkout <branch-name>
   ```

   Inicia la aplicación y prueba los selectores de alto contraste y modo claro en el navegador. Confirma que funcionan y que la configuración persiste al volver a cargar la página.

El agente personalizado de accesibilidad ha guiado a Copilot para que aplique prácticas recomendadas. Si encuentras problemas o mejoras posibles, menciona a **@copilot** en un comentario, como hiciste con las otras PR.

## Ejercicio opcional: seguir delegando

El agente en la nube resulta útil para asignarle tareas reales del backlog mientras te ocupas de otras cosas. Crea y asigna algunas incidencias más. Por ejemplo:

- crear un formulario de interés para patrocinadores en la página de detalles del juego;
- implementar la paginación en la página de juegos;
- añadir validación de entradas y gestión de errores a los helpers de acceso a datos.

## Resumen

Has completado el recorrido del agente en la nube. En estas lecciones:

- has revisado los archivos de instrucciones del repositorio para ver su efecto en el trabajo del agente;
- has asignado incidencias y observado cómo el agente prepara su entorno, planifica y trabaja de forma asíncrona;
- has creado y usado un agente personalizado de accesibilidad para añadir los modos de alto contraste y claro;
- has usado la página de agentes de Copilot para supervisar y guiar la sesión;
- has revisado e iterado sobre las PR, mencionando a `@copilot` para pedir cambios y aprobando los flujos de trabajo.

## Revisión y siguientes pasos

Has completado el recorrido del agente en la nube. Los otros recorridos complementan lo aprendido:

- 🖥️ **[Recorrido de VS Code](../../vscode/)**: explora el modo agente de Copilot Chat y la integración MCP desde el IDE.
- 💻 **[Recorrido de CLI](../../cli/)**: entrega dos cambios revisados desde el terminal mediante Plan y Autopilot, habilidades, un agente de QA, Playwright MCP, Agent Merge y la opción `/delegate` para volver a delegar en el agente en la nube.

En tu propio repositorio, también puedes:

- asignar al agente una incidencia de refactorización o cobertura de pruebas;
- crear un agente personalizado para otro ámbito;
- configurar `copilot-setup-steps.yml` para otra pila tecnológica.

## Recursos

- [GitHub Copilot][github-copilot]
- [Acerca de los agentes de Copilot][copilot-agents]
- [Asignar incidencias de GitHub a Copilot][assign-issue]
- [Buenas prácticas para el flujo de configuración del agente en la nube][cloud-agent-best-practices]
- [Configurar el firewall del agente en la nube][agent-firewall]

---

| [← Lección anterior: Gestionar agentes][previous-lesson] |
|:--|

[github-copilot]: https://github.com/features/copilot
[cloud-agent-overview]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[assign-issue]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/start-copilot-sessions
[setup-workflow]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[copilot-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-cloud-agent
[cloud-agent-best-practices]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-environment
[agent-firewall]: https://docs.github.com/copilot/how-tos/copilot-on-github/customize-copilot/customize-cloud-agent/customize-the-agent-firewall
[previous-lesson]: ../4-managing-agents/
