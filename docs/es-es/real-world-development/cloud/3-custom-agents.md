---
title: "Ejercicio 3 - Agentes personalizados"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

## ¿Qué son los agentes personalizados?

Los [agentes personalizados][custom-agents-concept] de GitHub Copilot son asistentes de IA especializados en tareas o ámbitos concretos del desarrollo. Se definen mediante archivos Markdown en `.github/agents` y permiten proporcionar instrucciones, prácticas recomendadas, patrones de código y conocimientos específicos. Los equipos pueden convertir su experiencia en agentes reutilizables: por ejemplo, un agente de accesibilidad que compruebe el cumplimiento de [WCAG][wcag], uno de seguridad o uno que mantenga patrones de pruebas coherentes.

Los agentes personalizados se definen en archivos Markdown de `.github/agents` o, de forma global, en `~/.copilot/agents`. Cada archivo tiene un frontmatter YAML con al menos `name` y `description`, seguido de un prompt Markdown que define el comportamiento, la experiencia y las instrucciones del agente.

### Diferencias entre los agentes personalizados y las habilidades de agente

Los agentes personalizados y las [habilidades de agente][agent-skills-concept] se definen principalmente mediante Markdown e indican a una IA cómo realizar ciertas operaciones. La diferencia principal es que el **agente personalizado** realiza el trabajo y las **habilidades** son herramientas.

Los agentes personalizados tienen su propia ventana de contexto y pueden coordinar habilidades e incluso otros agentes. En este laboratorio, el agente personalizado de accesibilidad revisará el sitio y lo actualizará conforme a las directrices de accesibilidad. Durante el trabajo podría usar habilidades para el flujo de solicitudes de incorporación de cambios o para ejecutar y gestionar pruebas.

> [!NOTE]
> No hay una única forma correcta de crear un agente personalizado. Pruébalo e itera para adaptarlo a tu entorno y tus necesidades.

[custom-agents-concept]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[agent-skills-concept]: https://docs.github.com/copilot/concepts/agents/about-agent-skills
[wcag]: https://www.w3.org/WAI/standards-guidelines/wcag/

En este ejercicio:

- aprenderás cómo se definen los agentes personalizados;
- asignarás una tarea a un agente personalizado.

## Escenario

Tailspin Toys quiere que su plataforma sea accesible para todo el mundo, independientemente de sus capacidades o preferencias visuales. Algunos usuarios han señalado que les cuesta leer el tema oscuro debido al bajo contraste entre el texto y el fondo. El equipo de diseño solicita un modo de alto contraste que se pueda activar y desactivar.

Implementarás esta función con un agente personalizado.

## Revisar el agente de accesibilidad

Ya se ha creado un agente personalizado de accesibilidad. Revisa sus instrucciones:

1. Vuelve a tu codespace y abre `.github/agents/accessibility.md`.
2. Observa el frontmatter YAML con los campos `name` y `description`.

> [!CAUTION]
> El frontmatter con `name` y `description` es obligatorio para los agentes personalizados.

3. Revisa las secciones sobre las responsabilidades principales, las buenas prácticas de accesibilidad, ejemplos de HTML/CSS/JavaScript y errores habituales.

## Crear y asignar una incidencia

Mission control es el centro de operaciones de los agentes. Permite asignar tareas, supervisarlas y redirigirlas o darles más indicaciones. Asigna al agente de accesibilidad la tarea de añadir el modo de alto contraste:

1. Abre tu repositorio y selecciona **Issues** → **New issue** → **Blank issue**.
2. Escribe `Add high contrast mode to website` en **Title**.
3. En **Description**, escribe:

   ```plaintext
   We need a high contrast mode for the site. There should be a toggle for high contrast which the user can set. It should store the setting in local storage on the browser.
   ```

4. Selecciona **Create**. En el lado derecho, selecciona **Assign to Copilot**.
5. Selecciona **Accessibility agent** en la lista de agentes personalizados.

   ![Ventana de asignación al agente en la nube con el agente de accesibilidad seleccionado](../../../_images/ex5-select-custom-agent.png)

6. Selecciona **Assign**. Copilot empezará a trabajar en segundo plano.

## Resumen y siguientes pasos

Has explorado los [agentes personalizados][custom-agents] de GitHub Copilot, asistentes especializados en tareas concretas. Permiten convertir la experiencia y los estándares del equipo en agentes reutilizables. En este ejercicio:

- has aprendido cómo se definen los agentes personalizados;
- has asignado una tarea a un agente personalizado.

Mientras Copilot implementa el modo de alto contraste, [supervisa y guía la sesión del agente][next-lesson] desde mission control.

## Recursos

- [Acerca de los agentes personalizados][custom-agents]
- [Preparar la organización para usar agentes personalizados][org-custom-agents]
- [Preparar la empresa para usar agentes personalizados][enterprise-custom-agents]

---

| [← Lección anterior: Agente en la nube de GitHub Copilot][previous-lesson] | [Siguiente lección: Supervisar y gestionar agentes →][next-lesson] |
|:--|--:|

[previous-lesson]: ../2-cloud-agent/
[next-lesson]: ../4-managing-agents/
[custom-agents]: https://docs.github.com/copilot/concepts/agents/cloud-agent/about-custom-agents
[org-custom-agents]: https://docs.github.com/copilot/how-tos/administer-copilot/manage-for-organization/prepare-for-custom-agents
[enterprise-custom-agents]: https://docs.github.com/copilot/how-tos/administer-copilot/manage-for-enterprise/manage-agents/prepare-for-custom-agents
