create sequence seq_person_discounts start 1;

select SETVAL('seq_person_discounts', (select max(id) + 1 from person_discounts));

alter table person_discounts
alter column id
set default NEXTVAL('seq_person_discounts');