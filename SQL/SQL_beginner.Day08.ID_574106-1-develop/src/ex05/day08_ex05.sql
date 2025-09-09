-- session #1
begin transaction isolation level read committed;
select sum(rating) from pizzeria;
select sum(rating) from pizzeria;
commit;
select sum(rating) from pizzeria;

-- session #2
begin transaction isolation level read committed;
insert into pizzeria (id, name, rating) values (10, 'Kazan Pizza', 5);
commit;
select sum(rating) from pizzeria;