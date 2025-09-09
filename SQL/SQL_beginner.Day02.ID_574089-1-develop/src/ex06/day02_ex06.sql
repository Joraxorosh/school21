select m.pizza_name, pz.name as pizzeria_name
from person_order as po
join person as p
on p.id = po.person_id
join menu as m
on m.id = po.menu_id
join pizzeria as pz
on pz.id = m.pizzeria_id
WHERE p.name IN ('Denis', 'Anna')
ORDER BY 1, 2