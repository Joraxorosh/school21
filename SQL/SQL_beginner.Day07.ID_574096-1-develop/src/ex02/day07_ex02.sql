(select name, count(*), 'order' as action_type
 from person_order po
 join menu m on m.id = po.menu_id
 join pizzeria p on p.id = m.pizzeria_id
 group by name
 order by 2 desc
 limit 3)
union
(select name, count(*), 'visit' as action_type
 from person_visits pv
 join pizzeria p on p.id = pv.pizzeria_id
 group by name
 order by 2 desc
 limit 3)
order by 3, 2 desc;