<script setup>
import { ref, watch } from "vue";

const dismissSecs = 10;
const dismissCountDown = ref(0);
const showDismissibleAlert = ref(false);

function showAlert() {
    dismissCountDown.value = dismissSecs;
}

watch(dismissCountDown, (val) => {
    if (val > 0) {
        setTimeout(() => {
            dismissCountDown.value--;
        }, 1000);
    }
});
</script>

<template>
  <v-container fluid>
    <!-- 기본 알림 -->
    <v-alert type="info" class="mb-3">
      Default Alert
    </v-alert>

    <!-- 성공 알림 -->
    <v-alert type="success" class="mb-3">
      Success Alert
    </v-alert>

    <!-- 닫을 수 있는 알림 -->
    <v-alert
      v-if="showDismissibleAlert"
      type="error"
      closable
      class="mb-3"
      @click:close="showDismissibleAlert = false"
    >
      Dismissible Alert!
    </v-alert>

    <!-- 카운트다운 알림 -->
    <v-alert
      v-if="dismissCountDown > 0"
      type="warning"
      closable
      class="mb-3"
      @click:close="dismissCountDown = 0"
    >
      <p>
        This alert will dismiss after {{ dismissCountDown }} seconds...
      </p>

      <v-progress-linear
        color="warning"
        :max="dismissSecs"
        :model-value="dismissCountDown"
        height="4"
      />
    </v-alert>

    <!-- 버튼 -->
    <v-btn color="info" class="mr-4" @click="showAlert">
      Show alert with count-down timer
    </v-btn>

    <v-btn color="info" @click="showDismissibleAlert = true">
      Show dismissible alert
      ({{ showDismissibleAlert ? 'visible' : 'hidden' }})
    </v-btn>
  </v-container>
</template>
