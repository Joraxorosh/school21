select person_order.order_date as order_date, (person.name || '(age:' || person.age || ')') as person_information
from person_order
natural join (select person.id as person_id, name, age
				from person) as person
order by order_date asc, person_information asc