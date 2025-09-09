(select pz.name as pizzeria_name
 from person as p
 join person_order as po 
 	on po.person_id = p.id
 join menu as m 
 	on m.id = po.menu_id
 join pizzeria as pz
 	on pz.id = m.pizzeria_id
 where p.gender = 'female'
 except
 select pz.name as pizzeria_name
 from person as p
 join person_order as po 
 	on po.person_id = p.id
 join menu as m 
 	on m.id = po.menu_id
 join pizzeria as pz 
 	on pz.id = m.pizzeria_id
 where p.gender = 'male')
union
(select pz.name as pizzeria_name
 from person as p
 join person_order as po 
 	on po.person_id = p.id
 join menu as m 
 	on m.id = po.menu_id
 join pizzeria as pz 
 	on pz.id = m.pizzeria_id
 where p.gender = 'male'
 except
 select pz.name as pizzeria_name
 from person as p
 join person_order as po 
 	on po.person_id = p.id
 join menu as m 
 	on m.id = po.menu_id
 join pizzeria as pz 
 	on pz.id = m.pizzeria_id
 where p.gender = 'female')
order by 1