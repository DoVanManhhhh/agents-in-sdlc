---
title: "Ejercicio 4 - Agentes personalizados"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

## ¿Qué son los agentes personalizados?

Los [agentes personalizados][custom-agents-concept] de GitHub Copilot son asistentes de IA especializados en tareas o ámbitos concretos del flujo de desarrollo. Se definen mediante archivos Markdown en la carpeta `.github/agents` del repositorio y permiten proporcionar a Copilot instrucciones, buenas prácticas, patrones de código y conocimientos específicos. Los equipos pueden convertir sus conocimientos en agentes reutilizables: por ejemplo, un agente de accesibilidad que compruebe el cumplimiento de [WCAG][wcag], uno de seguridad que aplique prácticas de programación segura o uno de pruebas que mantenga patrones coherentes.

Los agentes personalizados se definen en archivos Markdown en `.github/agents` del proyecto o, de forma global, en `~/.copilot/agents`. Cada archivo tiene un frontmatter YAML que incluye al menos `name` y `description`, seguido de un prompt Markdown que define el comportamiento, la experiencia y las instrucciones del agente.

### Diferencias entre los agentes personalizados y las habilidades de agente

Los agentes personalizados y las [habilidades de agente][agent-skills-concept] comparten algunos aspectos: ambos se definen principalmente mediante archivos Markdown e indican a una IA cómo realizar ciertas operaciones. La diferencia principal es que el **agente personalizado** realiza el trabajo y las **habilidades** son herramientas.

Los agentes personalizados tienen su propia ventana de contexto y pueden coordinar habilidades e incluso otros agentes. En este laboratorio, el agente personalizado de accesibilidad revisará el sitio y lo actualizará conforme a las directrices de accesibilidad. Durante el trabajo podría usar habilidades para el flujo de solicitudes de incorporación de cambios o para ejecutar y gestionar pruebas.

> [!NOTE]
> No hay una única forma correcta de crear un agente personalizado. Como cualquier función de IA, tendrás que probarla e iterar para adaptarla a tu entorno y tus necesidades.

[custom-agents-concept]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[agent-skills-concept]: https://docs.github.com/copilot/concepts/agents/about-agent-skills
[wcag]: https://www.w3.org/WAI/standards-guidelines/wcag/

## Escenario

Tailspin Toys quiere que su plataforma de financiación colectiva sea accesible para todo el mundo, independientemente de sus capacidades o preferencias visuales. Algunos usuarios han señalado que les cuesta leer el tema oscuro actual debido al bajo contraste entre el texto y el fondo. El equipo de diseño ha solicitado un modo de alto contraste que se pueda activar y desactivar.

La accesibilidad es importante y queremos implementar el cambio con rapidez. Usarás un agente personalizado para generar la funcionalidad.

En este ejercicio:

- revisarás un agente personalizado de accesibilidad;
- usarás ese agente en Copilot Chat para implementar un modo de alto contraste.

## Revisar el agente personalizado de accesibilidad

Ya se ha creado un agente personalizado de accesibilidad. Revisa su contenido para entender cómo guiará a Copilot.

Vuelve a tu codespace, abre un terminal y crea una rama nueva a partir de `main` para el trabajo de accesibilidad. Mantendrás la PR del filtrado del Ejercicio 3 separada:

```bash
git checkout main
git pull
git checkout -b accessibility-vscode
```

1. Abre `.github/agents/accessibility.md`.
2. Observa el frontmatter YAML con los campos `name` y `description`.

> [!CAUTION]
> El frontmatter con `name` y `description` es obligatorio para los agentes personalizados.

3. Revisa las secciones siguientes, que describen:
   - las responsabilidades principales al generar código para un sitio accesible;
   - las buenas prácticas de accesibilidad;
   - ejemplos de código HTML, CSS y JavaScript;
   - errores y problemas habituales.

## Usar el agente personalizado en Copilot Chat

VS Code muestra todos los agentes personalizados de `.github/agents` en el selector situado en la parte inferior de la vista Copilot Chat. Puedes seleccionar un agente personalizado para limitar una sesión a sus instrucciones y herramientas.

> [!TIP]
> **Abrir Copilot Chat**
>
> Antes de empezar, vuelve al codespace, abre el panel Copilot Chat y selecciona **New Chat** para iniciar una conversación nueva. El modo y el modelo varían según el ejercicio; cada paso lo indicará cuando sea relevante.

1. En el selector de agentes de Chat, selecciona **Agent** si todavía no está seleccionado.

   ![Selector de agentes en la vista Chat.](../../../_images/shared-chat-mode-selector.png)

2. Abre el selector de agentes en la parte inferior de Chat. Muestra el agente activo (por defecto, **default**).
3. Selecciona **Accessibility agent** en la lista de agentes.
4. Envía este prompt al agente de accesibilidad:

   ```plaintext
   Add a high-contrast mode to the site. There should be a toggle for high contrast which the user can set, and the setting should persist across page reloads using local storage on the browser.
   ```

5. Copilot explorará el código, propondrá cambios y editará los archivos del proyecto. Cada edición aparecerá en Chat con la ruta y las diferencias para que puedas revisarla.
6. El indicador **Files changed** se actualizará conforme el agente modifique archivos.

> [!NOTE]
> El proceso puede tardar varios minutos. Copilot hará cambios reales en el repositorio, como editar componentes Astro, CSS y las pruebas relacionadas.

Revisarás y guiarás el trabajo en curso en el siguiente ejercicio.

## Resumen y siguientes pasos

Has explorado los [agentes personalizados][custom-agents]: asistentes de GitHub Copilot especializados en tareas o ámbitos concretos. Permiten convertir la experiencia y los estándares del equipo en agentes reutilizables.

Has aprendido:

- cómo se definen los agentes personalizados;
- cómo seleccionar un agente personalizado en el modo agente de Copilot Chat.

A continuación, [supervisarás y guiarás el trabajo del agente][next-lesson]: revisarás los cambios mientras se producen y añadirás un selector de modo claro a la misma sesión.

## Recursos

- [Acerca de los agentes personalizados][custom-agents]
- [Crear agentes personalizados en el IDE][creating-custom-agents-ide]
- [Agentes personalizados en VS Code][custom-agents-vscode]
- [Configuración de agentes personalizados][custom-agents-config]
- [Agentes personalizados en awesome-copilot][awesome-copilot-agents]

---

| [← Lección anterior: Probar la funcionalidad con el servidor Playwright MCP][previous-lesson] | [Siguiente lección: Supervisar y gestionar agentes →][next-lesson] |
|:--|--:|

[previous-lesson]: ../3-mcp/
[next-lesson]: ../5-managing-agents/
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[creating-custom-agents-ide]: https://docs.github.com/copilot/how-tos/use-copilot-agents/cloud-agent/create-custom-agents-in-your-ide
[custom-agents-vscode]: https://code.visualstudio.com/docs/copilot/customization/custom-agents
[custom-agents-config]: https://docs.github.com/copilot/reference/custom-agents-configuration
[awesome-copilot-agents]: https://github.com/github/awesome-copilot/tree/main/agents
