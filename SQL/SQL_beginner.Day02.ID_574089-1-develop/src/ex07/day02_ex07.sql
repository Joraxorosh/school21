select pz.name as pizzeria_name
from menu as m
join pizzeria as pz
on pz.id = m.pizzeria_id
join person_visits as pv
on pv.pizzeria_id = pz.id
join person as p
on p.id = pv.person_id
where p.name = 'Dmitriy' and m.price < 800 and pv.visit_date = '2022-01-08'