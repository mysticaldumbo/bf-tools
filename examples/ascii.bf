this program originally was ment to print ascii values but didnt work but now it breaks and its kinda funny so i kept it
just type random characters til it breaks lol you'll know when it happends
i've added comments to explain what it was SUPPOSED to do
,     read first character
[     loop until end of input
  >   move to next cell
  ,[  loop until cell value is 0 (end of input)
    . output ASCII value of the character
    > move to next cell
    - decrement cell value
  ]
  <<  move back to the beginning
  ,   read next character
]