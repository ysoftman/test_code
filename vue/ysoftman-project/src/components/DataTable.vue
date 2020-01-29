<template>
  <v-container fluid>
    <p>
      <v-data-table :headers="headers" :items="desserts" :items-per-page="-1" class="elevation-2">
        <!-- 2.0 이전까지는 scoped slot 으로 아이템들을 생성해야 한다. -->
        <template v-slot:items="props">
          <td class="text-xs-right">{{ props.item.id }}</td>
          <td class="text-xs-right">{{ props.item.name }}</td>
          <td class="text-xs-right">{{ props.item.fruit }}</td>
        </template>
      </v-data-table>
    </p>
    <p>
      <!-- 2.0 이후부터는 scoped slot 를 사용하지 않아고 기본형태로 보인다. -->
      <v-data-table :headers="headers" :items="desserts" :items-per-page="-1" class="elevation-2"></v-data-table>
    </p>
  </v-container>
</template>

<script>
export default {
  name: "DataTable",
  data() {
    return {
      desserts: [
        { id: "1", name: "bill", fruit: "lemon" },
        { id: "2", name: "yoon", fruit: "apple" }
      ],
      headers: [
        {
          text: "ID",
          align: "left",
          value: "id",
          sortable: true,
          class: "subheading font-weight-bold red lighten-1 white--text"
        },
        {
          text: "이름",
          align: "left",
          value: "name",
          sortable: true,
          class: "subheading font-weight-bold green lighten-1 white--text"
        },
        {
          text: "과일",
          align: "left",
          value: "fruit",
          sortable: true,
          class: "subheading font-weight-bold blue lighten-1 white--text"
        }
      ]
    };
  },
  methods: {
    craeteItems() {
      // 아이템 리스트 추가
      this.desserts.push({ id: "3", name: "ysoftman", fruit: "orange" });
      this.desserts.push({ id: "4", name: "aaa", fruit: "banana" });
      this.desserts.push({ id: "5", name: "bbb", fruit: "grape" });

      let addid = 6;
      // vuex 에 저장된 arr 도 추가
      this.$store.state.arr.forEach((element, index) => {
        this.desserts.push({ id: addid+index, name: element, fruit: "ModifyArray 컴포넌트" });
      });

    }
  },

  // component 가 생성되면 수행
  created() {},
  // component 가 마운트 되기전 수행
  beforeMounted() {},
  // component 가 마운트 완료되면 수행
  mounted() {
    this.craeteItems();
  }
};
</script>
