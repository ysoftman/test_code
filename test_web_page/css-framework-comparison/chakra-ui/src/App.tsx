import { useEffect, useState } from "react";
import {
  Box,
  Button,
  Card,
  Checkbox,
  Container,
  Flex,
  Heading,
  HStack,
  Input,
  NativeSelect,
  Separator,
  Stack,
  Text,
} from "@chakra-ui/react";
import { useColorMode } from "./color-mode";
import chakraPkg from "@chakra-ui/react/package.json";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

// 모든 프레임워크 공통 테마 토글 아이콘 (라이브러리 없이 인라인 SVG, Material 아이콘 path)
const MOON_PATH =
  "M12 3c-4.97 0-9 4.03-9 9s4.03 9 9 9 9-4.03 9-9c0-.46-.04-.92-.1-1.36-.98 1.37-2.58 2.26-4.4 2.26-2.98 0-5.4-2.42-5.4-5.4 0-1.81.89-3.42 2.26-4.4-.44-.06-.9-.1-1.36-.1z";
const SUN_PATH =
  "M12 7c-2.76 0-5 2.24-5 5s2.24 5 5 5 5-2.24 5-5-2.24-5-5-5zM2 13h2c.55 0 1-.45 1-1s-.45-1-1-1H2c-.55 0-1 .45-1 1s.45 1 1 1zm18 0h2c.55 0 1-.45 1-1s-.45-1-1-1h-2c-.55 0-1 .45-1 1s.45 1 1 1zM11 2v2c0 .55.45 1 1 1s1-.45 1-1V2c0-.55-.45-1-1-1s-1 .45-1 1zm0 18v2c0 .55.45 1 1 1s1-.45 1-1v-2c0-.55-.45-1-1-1s-1 .45-1 1zM5.99 4.58c-.39-.39-1.03-.39-1.41 0-.39.39-.39 1.03 0 1.41l1.06 1.06c.39.39 1.03.39 1.41 0s.39-1.03 0-1.41L5.99 4.58zm12.37 12.37c-.39-.39-1.03-.39-1.41 0-.39.39-.39 1.03 0 1.41l1.06 1.06c.39.39 1.03.39 1.41 0 .39-.39.39-1.03 0-1.41l-1.06-1.06zm1.06-10.96c.39-.39.39-1.03 0-1.41-.39-.39-1.03-.39-1.41 0l-1.06 1.06c-.39.39-.39 1.03 0 1.41s1.03.39 1.41 0l1.06-1.06zM7.05 18.36c.39-.39.39-1.03 0-1.41-.39-.39-1.03-.39-1.41 0l-1.06 1.06c-.39.39-.39 1.03 0 1.41s1.03.39 1.41 0l1.06-1.06z";

function ThemeIcon({ dark }: { dark: boolean }) {
  return (
    <svg
      width="18"
      height="18"
      viewBox="0 0 24 24"
      fill="currentColor"
      aria-hidden="true"
      style={{ display: "block" }}
    >
      <path d={dark ? SUN_PATH : MOON_PATH} />
    </svg>
  );
}

const HEART_PATH =
  "M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z";

function HeartIcon() {
  return (
    <svg
      width="16"
      height="16"
      viewBox="0 0 24 24"
      fill="currentColor"
      aria-hidden="true"
      style={{ display: "block" }}
    >
      <path d={HEART_PATH} />
    </svg>
  );
}

export default function App() {
  const { colorMode, setColorMode, toggleColorMode } = useColorMode();

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  // 부모(비교 페이지)에서 일괄 테마 적용 메시지를 받는다.
  useEffect(() => {
    const onMsg = (e: MessageEvent) => {
      if (e.data?.type === "setTheme")
        setColorMode(e.data.dark ? "dark" : "light");
    };
    window.addEventListener("message", onMsg);
    return () => window.removeEventListener("message", onMsg);
  }, [setColorMode]);

  return (
    <Box minH="100vh">
      <Flex
        align="center"
        gap="3"
        px="6"
        py="3"
        borderBottomWidth="1px"
        borderColor="border"
      >
        <Heading fontSize="lg" fontWeight="semibold">
          Chakra UI
        </Heading>
        <Text fontSize="sm" color="fg.muted">
          Chakra UI v{chakraPkg.version} · 컴포넌트 라이브러리 (Panda 기반, zero
          runtime)
        </Text>
        <Button
          ml="auto"
          size="sm"
          variant="outline"
          onClick={toggleColorMode}
          aria-label="toggle dark mode"
        >
          <ThemeIcon dark={colorMode === "dark"} />
        </Button>
      </Flex>

      <Container maxW="3xl" py="8">
        <Stack gap="8">
          {/* Buttons */}
          <Box>
            <Heading fontSize="md" fontWeight="semibold" mb="3">
              Buttons
            </Heading>
            <HStack gap="3" wrap="wrap">
              <Button colorPalette="blue">Contained</Button>
              <Button colorPalette="blue" variant="outline">
                Outlined
              </Button>
              <Button colorPalette="blue" variant="ghost">
                Text
              </Button>
              <Button colorPalette="blue">
                <HeartIcon /> With Icon
              </Button>
              <Button colorPalette="blue" disabled>
                Disabled
              </Button>
            </HStack>
          </Box>

          <Separator />

          {/* Card */}
          <Box>
            <Heading fontSize="md" fontWeight="semibold" mb="3">
              Card
            </Heading>
            <Card.Root maxW="sm">
              <Card.Body>
                <Card.Title fontSize="md">Card title</Card.Title>
                <Card.Description>
                  같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                  비교합니다.
                </Card.Description>
              </Card.Body>
              <Card.Footer>
                <Button size="sm" variant="ghost" colorPalette="blue">
                  Share
                </Button>
                <Button size="sm" variant="ghost" colorPalette="blue">
                  Learn more
                </Button>
              </Card.Footer>
            </Card.Root>
          </Box>

          <Separator />

          {/* Form */}
          <Box>
            <Heading fontSize="md" fontWeight="semibold" mb="3">
              Form
            </Heading>
            <form
              onSubmit={(e) => {
                e.preventDefault();
                setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
              }}
            >
              <Stack gap="4" maxW="sm">
                <Stack gap="1">
                  <Text fontSize="sm">Name</Text>
                  <Input
                    value={name}
                    onChange={(e) => setName(e.target.value)}
                  />
                </Stack>

                <Stack gap="1">
                  <Text fontSize="sm">Role</Text>
                  <NativeSelect.Root>
                    <NativeSelect.Field
                      value={role}
                      onChange={(e) => setRole(e.currentTarget.value)}
                    >
                      {ROLES.map((r) => (
                        <option key={r} value={r}>
                          {r}
                        </option>
                      ))}
                    </NativeSelect.Field>
                    <NativeSelect.Indicator />
                  </NativeSelect.Root>
                </Stack>

                <Checkbox.Root
                  checked={agree}
                  onCheckedChange={(e) => setAgree(!!e.checked)}
                >
                  <Checkbox.HiddenInput />
                  <Checkbox.Control />
                  <Checkbox.Label>I agree to the terms</Checkbox.Label>
                </Checkbox.Root>

                <Button type="submit" colorPalette="blue" disabled={!agree}>
                  Submit
                </Button>
              </Stack>
            </form>

            {submitted && (
              <Box
                as="pre"
                mt="4"
                maxW="sm"
                overflow="auto"
                rounded="md"
                bg="bg.muted"
                p="4"
                fontSize="13px"
              >
                {submitted}
              </Box>
            )}
          </Box>
        </Stack>
      </Container>
    </Box>
  );
}
