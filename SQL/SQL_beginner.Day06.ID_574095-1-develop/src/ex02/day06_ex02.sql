select pe.name, m.pizza_name, m.price, trunc((m.price - m.price * (pd.discount / 100))) as discount_price, p.name                                    AS pizzeria_name
from person_order as po
join menu as m on m.id = po.menu_id
join person_discounts as pd on pd.person_id = po.person_id and pd.pizzeria_id = m.pizzeria_id
join person as pe on pe.id = po.person_id
join pizzeria as p on p.id = m.pizzeria_id
order by 1, 2;