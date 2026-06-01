import { useState } from "react";
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

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

export default function App() {
  const { colorMode, toggleColorMode } = useColorMode();

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

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
        <Heading size="md">Chakra UI</Heading>
        <Text fontSize="sm" color="fg.muted">
          컴포넌트 라이브러리 · v3 (Panda 기반)
        </Text>
        <Button
          ml="auto"
          size="sm"
          variant="outline"
          onClick={toggleColorMode}
          aria-label="toggle dark mode"
        >
          {colorMode === "dark" ? "☀️ Light" : "🌙 Dark"}
        </Button>
      </Flex>

      <Container maxW="3xl" py="8">
        <Stack gap="8">
          {/* Buttons */}
          <Box>
            <Heading size="sm" mb="3">
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
              <Button colorPalette="blue">❤ With Icon</Button>
              <Button colorPalette="blue" disabled>
                Disabled
              </Button>
            </HStack>
          </Box>

          <Separator />

          {/* Card */}
          <Box>
            <Heading size="sm" mb="3">
              Card
            </Heading>
            <Card.Root maxW="sm">
              <Card.Body>
                <Card.Title>Card title</Card.Title>
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
            <Heading size="sm" mb="3">
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
