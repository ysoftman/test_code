import { Button } from "@astryxdesign/core/Button";
import { Card } from "@astryxdesign/core/Card";
import { Divider } from "@astryxdesign/core/Divider";
import { useMediaQuery } from "@astryxdesign/core/hooks";
import { HStack, VStack } from "@astryxdesign/core/Layout";
import {
	SegmentedControl,
	SegmentedControlItem,
} from "@astryxdesign/core/SegmentedControl";
import { Selector } from "@astryxdesign/core/Selector";
import { StackItem } from "@astryxdesign/core/Stack";
import { StatusDot } from "@astryxdesign/core/StatusDot";
import type { TableColumn } from "@astryxdesign/core/Table";
import { pixel, proportional, Table } from "@astryxdesign/core/Table";
import { Text } from "@astryxdesign/core/Text";
import { TextInput } from "@astryxdesign/core/TextInput";
import { Token } from "@astryxdesign/core/Token";
import { MagnifyingGlassIcon } from "@heroicons/react/20/solid";
import { useMemo, useState } from "react";
import {
	Bar,
	BarChart,
	CartesianGrid,
	ResponsiveContainer,
	Tooltip,
	XAxis,
	YAxis,
} from "recharts";

type Level = "INFO" | "WARN" | "ERROR";
type LevelFilter = Level | "ALL";

// Series colors come from the theme's data-visualization tokens, so they stay
// in step with light and dark mode. Token colors below use the same hues.
const LEVEL_COLOR: Record<Level, string> = {
	INFO: "var(--color-data-categorical-blue)",
	WARN: "var(--color-data-categorical-orange)",
	ERROR: "var(--color-data-categorical-red)",
};
const LEVEL_TOKEN: Record<Level, "blue" | "orange" | "red"> = {
	INFO: "blue",
	WARN: "orange",
	ERROR: "red",
};

const AXIS_TICK = {
	fontSize: "var(--font-size-sm)",
	fill: "var(--color-text-secondary)",
};
const GRID_STROKE = "var(--color-border)";
// Structural sizes for the plot area (chart height and margins).
const CHART_HEIGHT = 128;
const CHART_MARGIN = { top: 4, right: 16, left: 16, bottom: 0 };

interface Bucket {
	t: string;
	info: number;
	warn: number;
	error: number;
}

// One hour in 2-minute buckets, with an error spike around 14:44 that the
// alert feature below would have caught.
const HISTOGRAM: Bucket[] = Array.from({ length: 30 }, (_, i) => {
	const minute = i * 2;
	const wave = Math.round(Math.sin(i / 3) * 40);
	const spike = i >= 21 && i <= 23 ? ([0, 120, 180, 90][i - 20] ?? 0) : 0;
	return {
		t: `14:${String(minute).padStart(2, "0")}`,
		info: 320 + wave + ((i * 37) % 60),
		warn: 18 + ((i * 13) % 22) + (spike > 0 ? 30 : 0),
		error: 4 + ((i * 7) % 9) + spike,
	};
});

interface LogLine extends Record<string, unknown> {
	id: string;
	time: string;
	level: Level;
	service: string;
	message: string;
}

const LOG_LINES: LogLine[] = [
	{
		id: "l1",
		time: "14:46:12.318",
		level: "ERROR",
		service: "payment-api",
		message: "upstream timeout after 3000ms (pg-primary:5432)",
	},
	{
		id: "l2",
		time: "14:46:12.102",
		level: "WARN",
		service: "payment-api",
		message: "retrying charge req_8f2c (attempt 2/3)",
	},
	{
		id: "l3",
		time: "14:46:11.877",
		level: "INFO",
		service: "checkout-web",
		message: "POST /api/orders 201 184ms",
	},
	{
		id: "l4",
		time: "14:46:11.540",
		level: "ERROR",
		service: "payment-api",
		message: "context deadline exceeded: SELECT … FROM ledger",
	},
	{
		id: "l5",
		time: "14:46:11.203",
		level: "INFO",
		service: "driftlog-agent",
		message: "flushed 4,812 lines to s3://logs-prod (1.2MB)",
	},
	{
		id: "l6",
		time: "14:46:10.966",
		level: "WARN",
		service: "checkout-web",
		message: "slow response GET /api/cart 1.84s",
	},
	{
		id: "l7",
		time: "14:46:10.512",
		level: "INFO",
		service: "payment-api",
		message: "charge ok req_77a1 amount=39000 KRW",
	},
	{
		id: "l8",
		time: "14:46:10.031",
		level: "ERROR",
		service: "payment-api",
		message: "upstream timeout after 3000ms (pg-primary:5432)",
	},
];

const TIME_RANGES = [
	{ value: "15m", label: "최근 15분" },
	{ value: "1h", label: "최근 1시간" },
	{ value: "24h", label: "최근 24시간" },
];

interface TooltipEntry {
	name: string;
	value: number;
	color: string;
}

function HistogramTooltip({
	active,
	payload,
	label,
}: {
	active?: boolean;
	payload?: TooltipEntry[];
	label?: string;
}) {
	if (!active || !payload?.length) {
		return null;
	}
	return (
		<Card padding={3} elevation="med">
			<VStack gap={1}>
				<Text type="supporting">{label}</Text>
				{payload.map((entry) => (
					<Text key={entry.name} type="supporting" hasTabularNumbers>
						{entry.name} {entry.value.toLocaleString("ko-KR")}
					</Text>
				))}
			</VStack>
		</Card>
	);
}

function LevelHistogram() {
	return (
		<ResponsiveContainer width="100%" height={CHART_HEIGHT}>
			<BarChart data={HISTOGRAM} margin={CHART_MARGIN} barCategoryGap={2}>
				<CartesianGrid vertical={false} stroke={GRID_STROKE} />
				<XAxis
					dataKey="t"
					tick={AXIS_TICK}
					axisLine={false}
					tickLine={false}
					interval={5}
				/>
				<YAxis hide />
				<Tooltip
					content={<HistogramTooltip />}
					cursor={{ fill: "var(--color-overlay-hover)" }}
				/>
				<Bar
					dataKey="info"
					name="INFO"
					stackId="level"
					fill={LEVEL_COLOR.INFO}
					isAnimationActive={false}
				/>
				<Bar
					dataKey="warn"
					name="WARN"
					stackId="level"
					fill={LEVEL_COLOR.WARN}
					isAnimationActive={false}
				/>
				<Bar
					dataKey="error"
					name="ERROR"
					stackId="level"
					fill={LEVEL_COLOR.ERROR}
					isAnimationActive={false}
				/>
			</BarChart>
		</ResponsiveContainer>
	);
}

/**
 * Responsive contract for the preview (useMediaQuery, 640px):
 *   >640  query | range | run on one row; table: time | level | service | message
 *   <=640 query takes its own row; service column drops, time loses millis
 */
function useLogColumns(isNarrow: boolean): TableColumn<LogLine>[] {
	return useMemo(() => {
		const columns: TableColumn<LogLine>[] = [
			{
				key: "time",
				header: "시간",
				width: pixel(isNarrow ? 84 : 128),
				renderCell: (row) => (
					<Text type="code" color="secondary" hasTabularNumbers maxLines={1}>
						{isNarrow ? row.time.slice(0, 8) : row.time}
					</Text>
				),
			},
			{
				key: "level",
				header: "Level",
				width: pixel(84),
				renderCell: (row) => (
					<Token size="sm" label={row.level} color={LEVEL_TOKEN[row.level]} />
				),
			},
		];
		if (!isNarrow) {
			columns.push({
				key: "service",
				header: "서비스",
				width: pixel(136),
				renderCell: (row) => (
					<Text type="code" maxLines={1}>
						{row.service}
					</Text>
				),
			});
		}
		columns.push({
			key: "message",
			header: "메시지",
			width: proportional(1, { minWidth: 160 }),
			renderCell: (row) => (
				<Text type="code" maxLines={1}>
					{row.message}
				</Text>
			),
		});
		return columns;
	}, [isNarrow]);
}

const wait = (ms: number) =>
	new Promise<void>((resolve) => {
		window.setTimeout(resolve, ms);
	});

export function ProductPreview() {
	const [query, setQuery] = useState(
		'{namespace="prod", cluster="seoul-1"} != "healthz"',
	);
	const [range, setRange] = useState("1h");
	const [level, setLevel] = useState<LevelFilter>("ALL");
	const isNarrow = useMediaQuery("(max-width: 640px)");
	const columns = useLogColumns(isNarrow);

	const rows = useMemo(
		() =>
			level === "ALL" ? LOG_LINES : LOG_LINES.filter((l) => l.level === level),
		[level],
	);

	const queryInput = (
		<TextInput
			label="쿼리"
			isLabelHidden
			value={query}
			onChange={setQuery}
			startIcon={MagnifyingGlassIcon}
			width="100%"
			hasAutoCorrect={false}
			autoCapitalize="off"
		/>
	);
	const rangeSelector = (
		<Selector
			label="시간 범위"
			isLabelHidden
			options={TIME_RANGES}
			value={range}
			onChange={setRange}
		/>
	);
	const runButton = (
		<Button label="실행" variant="primary" clickAction={() => wait(600)} />
	);

	return (
		<Card padding={0} elevation="med">
			<VStack gap={0}>
				<HStack gap={3} vAlign="center" hAlign="between" padding={4}>
					<HStack gap={2} vAlign="center">
						<Text weight="semibold">로그 탐색</Text>
						<Token size="sm" label="prod" />
					</HStack>
					<HStack gap={2} vAlign="center">
						<StatusDot variant="success" label="라이브 테일 연결됨" isPulsing />
						<Text type="supporting">라이브 테일</Text>
					</HStack>
				</HStack>
				<Divider />
				<VStack gap={4} padding={4}>
					{isNarrow ? (
						<VStack gap={2}>
							{queryInput}
							<HStack gap={2} vAlign="end">
								<StackItem size="fill">{rangeSelector}</StackItem>
								{runButton}
							</HStack>
						</VStack>
					) : (
						<HStack gap={2} vAlign="end">
							<StackItem size="fill">{queryInput}</StackItem>
							{rangeSelector}
							{runButton}
						</HStack>
					)}
					<HStack gap={3} vAlign="center" hAlign="between" wrap="wrap">
						<Text type="supporting" hasTabularNumbers>
							12,483줄 · 0.84초 · 14:44 전후 ERROR 급증
						</Text>
						<SegmentedControl
							label="로그 레벨"
							size="sm"
							value={level}
							onChange={(value) => setLevel(value as LevelFilter)}
						>
							<SegmentedControlItem value="ALL" label="전체" />
							<SegmentedControlItem value="INFO" label="INFO" />
							<SegmentedControlItem value="WARN" label="WARN" />
							<SegmentedControlItem value="ERROR" label="ERROR" />
						</SegmentedControl>
					</HStack>
					<LevelHistogram />
				</VStack>
				<Divider />
				<Table
					data={rows}
					columns={columns}
					idKey="id"
					density="compact"
					textOverflow="truncate"
					hasHover
				/>
			</VStack>
		</Card>
	);
}
