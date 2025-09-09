select p.name
from person as p
join person_order as po 
on po.person_id = p.id
join menu as m
on m.id = po.menu_id
where p.gender = 'female' and m.pizza_name = 'pepperoni pizza'
intersect
select p.name
from person as p
join person_order as po 
on po.person_id = p.id
join menu as m 
on m.id = po.menu_id
where p.gender = 'female' and m.pizza_name = 'cheese pizza'
order by 1